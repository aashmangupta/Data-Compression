//
// Created by Aashman Gupta on 2/14/18.
//

#ifndef __HEAP_INCLUDED__
#define __HEAP_INCLUDED__

#include <stdio.h>

typedef struct heap HEAP;

extern HEAP *newHEAP(
        void (*)(void *,FILE *),    //display
        int (*)(void *,void *),     //compare
        void (*)(void *));          //free
extern void insertHEAP(HEAP *h,void *value);
extern void buildHEAP(HEAP *h);
extern void *peekHEAP(HEAP *h);
extern void *extractHEAP(HEAP *h);
extern int  sizeHEAP(HEAP *h);
extern void displayHEAP(HEAP *h,FILE *fp);
extern void displayHEAPdebug(HEAP *h,FILE *fp);
extern void freeHEAP(HEAP *h);

#endif

