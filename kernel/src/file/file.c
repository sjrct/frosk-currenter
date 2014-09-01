//
// file/file.c
//

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"

static void assure(file_t * f)
{
	if (!(f->flags & FILE_PRESENT)) {
		// TODO
		assert(0);
	}
}

file_t * resolve(file_t * f)
{
	assure(f);
	while (f->type == FILE_INDIRECT) {
		f = f->x.indirect;
		assure(f);
	}
	return f;
}

static file_t ** retrieve_h(const char * path, file_t ** dir, file_t ** par)
{
	int cmp;
	const char * start;
	file_t ** p;

	*dir = resolve(*dir);
	if ((*dir)->type != FILE_DIRECTORY) return NULL;

	start = path;
	while (*path != '/' && *path) path++;

	p = &(*dir)->x.root;
	*par = NULL;
	while (*p != NULL) {
		cmp = strncmp(start, (*p)->name, path-start);

		if (cmp < 0) {
			*par = *p;
			p = &(*p)->left;
		} else if (cmp > 0) {
			*par = *p;
			p = &(*p)->right;
		} else {
			if (!*path) {
				return p;
			} else {
				return retrieve_h(path + 1, dir, par);
			}
		}
	}

	return p;
}

file_t * retrieve(const char * path, file_t * dir)
{
	file_t ** x, * par;
	x = retrieve_h(path, &dir, &par);
	return x == NULL ? NULL : *x;
}

file_t * create(char * path, file_type type, file_t * dir)
{
	int i, len, s;
	file_t * par;
	file_t * dumb;
	file_t ** p;

	if (dir != NULL) {
		p = retrieve_h(path, &dir, &par);
		if (p == NULL || *p != NULL)  return NULL;
	} else {
		p = &dumb;
	}

	len = strlen(path);
	for (i = s = 0; i < len; i++) {
		if (path[i] == '/') s = i + 1;
	}

	*p = malloc(sizeof(file_t));
	(*p)->name  = malloc(len - s + 1);
	strcpy((*p)->name, path + s);
	(*p)->type  = type;
	(*p)->flags = FILE_PRESENT | FILE_WRITTEN;
	(*p)->left  = NULL;
	(*p)->right = NULL;
	(*p)->par   = par;
	(*p)->dir   = dir;
	(*p)->x.data.size = 0;

	return *p;
}

static file_t * leftmost(file_t * x)
{
	while (x != NULL && x->left != NULL) x = x->left;
	return x;
}

file_t * first_file(file_t * d)
{
	return d->type == FILE_DIRECTORY ? leftmost(d->x.root) : NULL;
}

file_t * next_file(file_t * prv)
{
	if (prv->right == NULL) {
		while (prv->par != NULL && prv->par->left != prv) prv = prv->par;
		prv = prv->par;
	} else {
		prv = prv->right;
	}
	return prv;
}

size_t write(void * buf, size_t addr, size_t size, file_t * file)
{
	file = resolve(file);

	if (file->type != FILE_DATA) return 0;

	if (file->x.data.size < addr + size) {
		file->x.data.data = realloc(file->x.data.data, addr + size);
		file->x.data.size = addr + size;
	}

	memcpy(file->x.data.data + addr, buf, size);
	file->flags &= ~FILE_WRITTEN;

	return size;
}

size_t read(void * buf, size_t addr, size_t size, file_t * file)
{
	file = resolve(file);

	if (file->type != FILE_DATA) return 0;

	if (file->x.data.size < addr + size) {
		size = file->x.data.size < addr ? 0 : file->x.data.size - addr;
	}

	memcpy(buf, file->x.data.data, size);
	return size;
}

