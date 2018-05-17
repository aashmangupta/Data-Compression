#ifndef __HUFF_INCLUDED__
#define __HUFF_INCLUDED__

#include <stdio.h>

typedef struct huffNode HUFFNODE;

extern HUFFNODE *newHUFFNODE(char character, int weight);
extern char getCharacter(HUFFNODE *h);
extern int getWeight(HUFFNODE *h);
extern void displayNode(HUFFNODE *h);
extern void setLeft(HUFFNODE *parent, HUFFNODE *child);
extern void setRight(HUFFNODE *parent, HUFFNODE *child);
extern void setParent(HUFFNODE *child, HUFFNODE *parent);
extern void findLeaves(HUFFNODE* finalNode, int count);
extern char* returnCode(int i);

#endif
