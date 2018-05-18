#ifndef __HUFF_INCLUDED__
#define __HUFF_INCLUDED__

#include <stdio.h>

typedef struct Huff_Node_Struct {
	char character;
	int weight;
	int size;
	char* code;
	struct Huff_Node_Struct* left;
	struct Huff_Node_Struct* right;
	struct Huff_Node_Struct* parent;
} HuffNode;

// Maybe change this method name to createHuffNode(char, int)
HuffNode *newHUFFNODE(char character, int weight);
char getCharacter(HuffNode *h);
int getWeight(HuffNode *h);
void displayNode(HuffNode *h);
void setLeft(HuffNode *parent, HuffNode *child);
void setRight(HuffNode *parent, HuffNode *child);
void setParent(HuffNode *child, HuffNode *parent);
void findLeaves(HuffNode* finalNode, int count);
char* returnCode(int i);

#endif
