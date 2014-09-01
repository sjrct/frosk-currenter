//
// file/file.h
//

#ifndef FS_FS_H
#define FS_FS_H

#include <stddef.h>

typedef struct fptr_t fptr_t;
typedef struct file_t file_t;

// These definitions are used to make the 'flags' bitmask
// Note only FILE_DATA, FILE_DIRECTORY, and FILE_METADATA are passed to the
//   filesystem create function.
#define FILE_DATA      0x01
#define FILE_DIRECTORY 0x02
#define FILE_METADATA  0x04
#define FILE_INDIRECT  0x08 // This implies FILE_DATA & FILE_DIRECTORY are not set
#define FILE_VIRTUAL   0x10
#define FILE_PRESENT   0x20
#define FILE_WRITTEN   0x40

// This mask is used to makes the flags in to the 'type' field which is passed
// to the file system 'create' function.
#define FILE_TYPEMASK  0x07

struct file_ptr_t {
	// TODO add locking to this structure

	char * name;

	// A bitmask of the FILE_* definitions from above
	unsigned flags;

	// The directory in which the file is contained
	fptr_t * dir;

	// Used in the formation of the per-directory binary tree of files
	fptr_t * par;
	fptr_t * left;
	fptr_t * right;

	// Only significant if the FILE_DATA bit is set
	void * data;
	size_t data_size;

	// Only significant if the FILE_DIRECTORY bit is set
	fptr_t * root;

	// Only significant if the FILE_INDIRECT bit is set
	fptr_t * indirect;
};

struct file_t {
	fptr_t * ptr;
	void * fs_spec;
};

// This will resolve an indirect fptr such that it becomes a direct fptr
file_t * resolve(file_t * file);

// This will retrieve a file_t structure with the given relative path within
//   the given directory
fptr_t * retrieve(const char * path, fptr_t * directory);

// Creates a type
file_t * create(char * name, unsigned type, file_t * directory);

// Only usable when FILE_DATA is set
file_t * first_file(file_t

// Only usable when FILE_DIRECTORY is set
file_t * first_file(file_t * directory);
file_t * next_file(file_t * directory);

// Only usable when FILE_METADATA is set


#endif
