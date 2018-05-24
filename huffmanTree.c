#include "huffmanTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char code[100000];
char* codeTable[95];


HuffNode *newHUFFNODE(char character, int weight) {
	HuffNode* currNode = malloc(sizeof(HuffNode));
	currNode->character = character;
	currNode->weight = weight;
	currNode->code = 0;
	currNode->size = 0;
	currNode->left = 0;
	currNode->right = 0;
	currNode->parent = 0;
	return currNode;
}

char getCharacter(HuffNode *h) {
	if (!h) {
		return 0;
	}
	return h->character;
}

int getWeight(HuffNode *h) {
	if(h == 0) {
		return 0;
	}
	return h->weight;
}

void displayNode(HuffNode *h) {
	if (!h) {
		return;
	}
	if (!h->character) {
		printf("XX %d\n", h->weight);
	} else {
		printf("%c %d\n", h->character, h->weight);
	}
	if (h->left != 0) {
		printf("L: ");
	}
	displayNode(h->left);
	if (h->right != 0) {
		printf("R: ");
	}
	displayNode(h->right);
}

void setLeft(HuffNode *parent, HuffNode *child) {
	parent->left = child;
}

void setRight(HuffNode *parent, HuffNode *child) {
	parent->right = child;
}

void setParent(HuffNode *child, HuffNode *parent) {
	child->parent = parent;
}

void findLeaves(HuffNode* finalNode, int count) {
	if (!finalNode) {
		return;
	}
	if (!finalNode->left && !finalNode->right) {
		codeTable[finalNode->character - 32] = malloc(strlen(code) * sizeof(char));
		strcpy(codeTable[finalNode->character - 32], code);
		code[strlen(code)-1] = '\0';
		return;
	}
	if (finalNode->left) {
		strcat(code, "0");
		findLeaves(finalNode->left, count);
	}
	if (finalNode->right) {
		strcat(code, "1");
		findLeaves(finalNode->right, count);
	}
	code[strlen(code)-1] = '\0';
}

char* returnCode(int i) {
	return codeTable[i];
}


