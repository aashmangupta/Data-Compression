#ifndef __QUEUE_INCLUDED__
#define __QUEUE_INCLUDED__

#include <stdio.h>

typedef struct queue QUEUE;

extern QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *));
extern void enqueue(QUEUE *items,void *value);
extern void *dequeue(QUEUE *items);
extern void *peekQUEUE(QUEUE *items);
extern int sizeQUEUE(QUEUE *items);
extern void displayQUEUE(QUEUE *items,FILE *);
extern void displayQUEUEdebug(QUEUE *items,FILE *);
extern void freeQUEUE(QUEUE *items);

#endif

