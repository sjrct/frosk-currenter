//
// sched/proc.h
//

#ifndef SCHED_PROC_H
#define SCHED_PROC_H

#include "../lock.h"

enum {
	STATE_INVALID = -1,
	STATE_READY,
	STATE_SETUP,
	STATE_RUNNING,
	STATE_WAITING,
	STATE_STOPPED,
};

typedef struct thread thread_t;
typedef struct process process_t;

struct process {
	lock_t lock;
	char ** argv;
	int argc;
	thread_t * first;
};

struct thread {
	lock_t lock;
	process_t * proc;
	thread_t * next;
	int priority;
	int state;
};

// Creates a new (user) process
process_t * execute(int argc, char ** argv);

// Creates a new user thread
thread_t * uspawn(void);

// Creates a new kernel thread
thread_t * kspawn(void (* enter)(void));

// Yeilds control of the current thread to the kernel
void yield(void);

#endif
