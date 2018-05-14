#ifndef __HUFF_INCLUDED__
#define __HUFF_INCLUDED__

#include <stdio.h>

typedef struct huffNode HUFFNODE;
typedef struct huffTree HUFFTREE;

extern HUFFNODE *newHUFFNODE(char character, int weight);
extern HUFFTREE* newHUFFTREE();
extern char getCharacter(HUFFNODE *h);
extern int getWeight(HUFFNODE *h);
extern void displayNodes(HUFFNODE *h);

#endif
