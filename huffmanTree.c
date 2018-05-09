#include "huffmanTree.h"
#include <stdio.h>

struct huffNode {
	char character;
	int weight;
	HUFFNODE* left;
	HUFFNODE* right;
	int size;
};


