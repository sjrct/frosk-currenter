//
// sched/proc.c
//

#include <stdlib.h>
#include "proc.h"

process_t * execute(int argc, char ** argv)
{
	process_t * p = malloc(sizeof(process_t));

	init_lock(&p->lock);
	p->argv = argv;
	p->argc = argc;
	p->first = NULL;

	return p;
}

static set_state(thread_t * t, int state)
{
	lock(&t->lock);
	t->state = state;
	unlock(&t->lock);
}

static thread_t * spawn(process_t * p)
{
	thread_t * t = malloc(sizeof(thread_t));

	// initialize stuff
	init_lock(&t->lock);
	t->priority = 0;
	t->state = STATE_SETUP;
	t->proc = p;

	// add to the process' thread list
	lock(&p->lock);
	t->next = p->first;
	p->first = t;
	unlock(&p->lock);

	set_state(STATE_READY);
	return t;
}

thread_t * uspawn(process_t * p)
{
	thread_t * t = spawn(p);
	return t;
}

thread_t * kspawn(void (* foo)(void))
{
	thread_t * t = spawn();
	return t;
}

void yield(thread_t * t)
{
	// TODO this function
}
