#include "huffmanTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char code[100000];
char* codeTable[26];

struct huffNode {
	char character;
	int weight;
	int size;
	char* code;
	HUFFNODE* left;
	HUFFNODE* right;
	HUFFNODE* parent;
};

HUFFNODE *newHUFFNODE(char character, int weight) {
	HUFFNODE* currNode = malloc(sizeof(HUFFNODE));
	currNode->character = character;
	currNode->weight = weight;
	currNode->code = 0;
	currNode->size = 0;
	currNode->left = 0;
	currNode->right = 0;
	currNode->parent = 0;
	return currNode;
}

char getCharacter(HUFFNODE *h) {
	if(h == 0) {
		return  0;
	}
	return h->character;
}

int getWeight(HUFFNODE *h) {
	if(h == 0) {
		return 0;
	}
	return h->weight;
}

void displayNode(HUFFNODE *h) {
	if(h == 0) {
		return;
	}
	if(h->character == 0) {
		printf("XX %d\n", h->weight);
	}
	else {
		printf("%c %d\n", h->character, h->weight);
	}
	if(h->left != 0) printf("L: ");
	displayNode(h->left);
	if(h->right != 0) printf("R: ");
	displayNode(h->right);
}

void setLeft(HUFFNODE *parent, HUFFNODE *child) {
	parent->left = child;
}

void setRight(HUFFNODE *parent, HUFFNODE *child) {
	parent->right = child;
}

void setParent(HUFFNODE *child, HUFFNODE *parent) {
	child->parent = parent;
}

void findLeaves(HUFFNODE* finalNode, int count) {
	if(finalNode == 0) {
		return;
	}
	if(!finalNode->left && !finalNode->right) {
		codeTable[finalNode->character - 97] = malloc(strlen(code) * sizeof(char));
		strcpy(codeTable[finalNode->character - 97], code);
		code[strlen(code)-1] = '\0';
		return;
	}
	if(finalNode->left) {
		strcat(code, "0");
		findLeaves(finalNode->left, count);
	}
	if(finalNode->right) {
		strcat(code, "1");
		findLeaves(finalNode->right, count);
	}
	code[strlen(code)-1] = '\0';
}

char* returnCode(int i) {
	return codeTable[i];
}


