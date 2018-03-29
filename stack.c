//
// Created by Aashman Gupta on 1/18/18.
// A stack based on a doubly-linked-list.

#include "stack.h"
#include <stdlib.h>
#include <assert.h>
#include "dll.h"
#include <stdio.h>

struct stack{
    DLL* linkedList;
    int index;
    void (*display)(void*, FILE*);
    void (*free)(void*);
};

STACK *newSTACK(void (*d)(void *,FILE *),void (*f)(void *)) {
    STACK *items = malloc(sizeof(STACK));

    assert(items != 0);

    items->linkedList = newDLL(d, f);
    items->index = -1;
    items->display = d;
    items->free = f;

    return items;
}

void push(STACK *items,void *value) {
    items->index += 1;
    insertDLL(items->linkedList, items->index, value);

    /*if(items == NULL) {
        return;
    }

    if(items->topIndex >= items->capacity - 1) {
        items->arr = realloc(items->arr, 2 * (items->capacity * sizeof(void*)));    //doubles the current memory
        items->capacity *= 2;
    }

    items->topIndex++;              //items->arr[items->topIndex] = malloc(sizeof(void*));
    items->arr[items->topIndex] = value;*/
}

void *pop(STACK *items) {
    assert(items->index >= 0);

    void* removedVal = removeDLL(items->linkedList, items->index);
    items->index -= 1;
    return removedVal;
    /*assert(items->topIndex >= 0);

    void* temp = items->arr[items->topIndex];
    //items->free(items->arr[items->topIndex]);
    items->topIndex--;

    if(items->topIndex < (items->capacity * .25)) {
        items->arr = realloc(items->arr, (items->capacity / 2) * sizeof(void*));    //get rid of unnecessary memory
        items->capacity = items->capacity / 2;
    }

    return temp;*/
}

void *peekSTACK(STACK *items) {
    assert(items->index >= 0);
    return getDLL(items->linkedList, items->index);
}

int sizeSTACK(STACK *items) {
    return items->index + 1;
}

void freeSTACK(STACK *items) {
    if(items == NULL) {
        return;
    }
    freeDLL(items->linkedList);
    free(items);
}

void displaySTACK(STACK *items,FILE *fp) {
    void *currElement;

    fprintf(fp, "|");
    for(int i = items->index; i >= 0; i--) {
        currElement = getDLL(items->linkedList, i);
        items->display(currElement, fp);
        if(i != 0) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "|");
    //displayDLL(items->linkedList, stdout);
    //displayDLLdebug(items->linkedList, stdout);
}

void displaySTACKdebug(STACK *items,FILE *fp){
    fprintf(fp, "head->{{");

    for(int i = items->index; i >= 0; i--) {
        items->display(getDLL(items->linkedList, i ), fp);
        if(i != 0) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "}}");

    fprintf(fp, ",tail->{{");

    if(items->index >= 0) {
        items->display(getDLL(items->linkedList, 0), fp);
    }
    fprintf(fp, "}}");
}


