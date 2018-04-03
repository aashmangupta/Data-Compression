#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"bst.h"
#include"string.h"
#include"integer.h"

int dataTable[26];

void populateTable(char currChar);
int getMinIndex();
void makeTree();
BST* tree;

int main(int argc, char** argv) {
	int count = 0;
	char currChar;
	tree = newBST(displaySTRING, compareSTRING, 0,freeSTRING);

	if(argc < 2) {
		printf("Type in a data file after ./a.out.\n");
		return 0;
	}

	char* dataFile = argv[argc - 1];
	
	FILE* fp = fopen(dataFile, "r");
										//Make a loop so that characters get put in the place they belong in the alphabet.
	for(int i = 0; i < 26; i++) {		//This loop puts in initial values into 2D array.
		dataTable[i] = 0;
	}
	
	fscanf(fp, "%c", &currChar);
	while(!feof(fp)) {
		populateTable(currChar);
		fscanf(fp, "%c", &currChar);	
	}

	makeTree();
	/*for(int i = 0; i < 26; i++) {		//Use this to print dataTable
		printf("%c: ", (char) i+97);
		printf("%d\n", dataTable[i]);
	}*/
	displayBST(tree, stdout);
return 0;
}

int getMinIndex() {
	int min = 10000;
	int retVal;

	for(int i = 0; i < 26; i++) {
		if((dataTable[i] < min) && (dataTable[i] > 0)) {
			min = dataTable[i];
			retVal = i;
		}
	}
	return retVal;
}

void makeTree() {						//Dont forget to intitalize the frequency of the index to 0, after using it.
	int index1, index2;
	
	if(sizeBST(tree) == 0) {
		index1 = getMinIndex();
		index2 = getMinIndex();
		insertBST(tree, newINTEGER(dataTable[index1] + dataTable[index2]));
		BSTNODE* parent = getBSTroot(tree);
		BSTNODE* leftChild = newBSTNODE(newINTEGER(dataTable[index1]));
		BSTNODE* rightChild = newBSTNODE(newINTEGER(dataTable[index2]));
		setBSTNODEleft(parent, leftChild);
		setBSTNODEright(parent, rightChild);
		dataTable[index1] = 0;
		dataTable[index2] = 0;
	}
}

void populateTable(char currChar) {
	if(isalpha(currChar)) {
		int index = currChar - 97;
		dataTable[index]++;
	}
}
