//
// kernel/src/semaphore.h
//

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

typedef int semaphore_t;

int read_wait(semaphore_t *);
int write_wait(semaphore_t *);
void read_signal(semaphore_t *);
void write_signal(semaphore_t *);

#endif
