//
// Created by Aashman Gupta on 1/24/18.
// A queue based on a singly-linked-list.

#include "queue.h"
#include <stdlib.h>
#include <assert.h>
#include "sll.h"
#include <stdio.h>

struct queue {
    SLL* linkedList;
    int front;
    int rear;
    int size;
    void (*display)(void*, FILE*);
    void (*free)(void*);
};

QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *)) {
    QUEUE* items = malloc(sizeof(QUEUE));

    assert(items != 0);

    items->linkedList = newSLL(d, f);
    items->front = -1;
    items->rear = -1;
    items->size = 0;
    items->free = f;
    items->display = d;

    return items;
}

void enqueue(QUEUE *items,void *value) {
    if(items->size == 0) {
        items->front = 0;
    }

    items->rear++;
    items->size++;

    insertSLL(items->linkedList, items->rear, value);
}

void *dequeue(QUEUE *items) {
    assert(items->size > 0);
    void* returnVal = getSLL(items->linkedList, items->front);
    removeSLL(items->linkedList, items->front);
    items->rear--;
    items->size--;
    return returnVal;
}

void *peekQUEUE(QUEUE *items) {
    assert(items->size > 0);
    return getSLL(items->linkedList, 0);
}

int sizeQUEUE(QUEUE *items) {
    return items->size;
}

void displayQUEUE(QUEUE *items,FILE *fp) {
    //int temp = items->front;
    void* currElement;

    fprintf(fp, "<");
    for(int i = 0; i < items->size; i++) {
        currElement = getSLL(items->linkedList, i);
        items->display(currElement, fp);
        if(i < items->size - 1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, ">");
}

void displayQUEUEdebug(QUEUE *items,FILE *fp) {
    displaySLLdebug(items->linkedList, fp);
}

void freeQUEUE(QUEUE *items) {
    if(items == NULL) {
        return;
    }
    freeSLL(items->linkedList);
    free(items);
}






