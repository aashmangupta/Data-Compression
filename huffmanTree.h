#ifndef __HUFF_INCLUDED__
#define __HUFF_INCLUDED__

#include <stdio.h>

typedef struct huffNode HUFFNODE;

extern HUFFNODE *newHUFFNODE(char character, int weight);
extern int getWeight(HUFFNODE *h);
extern char getCharacter(HUFFNODE *h);

#endif
