#include "huffmanTree.h"
#include <stdio.h>
#include <stdlib.h>

struct huffNode {
	char character;
	int weight;
	int size;
	HUFFNODE* left;
	HUFFNODE* right;
	HUFFNODE* parent;
};

struct huffTree {
	int weight;
	HUFFNODE* root;
	HUFFNODE* insertPos;
};

HUFFTREE* newHUFFTREE() {
	HUFFTREE* currTree = malloc(sizeof(HUFFTREE));
	currTree->weight = 0;
	currTree->root = 0;
	currTree->insertPos = 0;
	return currTree;
}

HUFFNODE *newHUFFNODE(char character, int weight) {
	HUFFNODE* currNode = malloc(sizeof(HUFFNODE));
	currNode->character = character;
	currNode->weight = weight;
	currNode->size = 0;
	currNode->left = 0;
	currNode->right = 0;
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

void displayNodes(HUFFNODE *h) {
	printf("%c %d\n", h->character, h->weight);
}

/*void insert(HUFFTREE* h, HUFFNODE* currNode) {

}*/
