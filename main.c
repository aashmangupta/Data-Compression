#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"string.h"
#include"integer.h"
#include"huffmanTree.h"

int dataTable[26];
HUFFNODE* nodeArr[26];
int treeArrIndex = 0;

void populateTable(char currChar);
int getMinIndex();
void makeIndividualNodes(int index);

int main(int argc, char** argv) {
	int count = 0;
	char currChar;

	if(argc < 2) {
		printf("Type in a data file after ./a.out.\n");
		return 0;
	}

	char* dataFile = argv[argc - 1];
	
	FILE* fp = fopen(dataFile, "r");

	for(int i = 0; i < 26; i++) {		//This loop puts in initial values into 2D array.
		dataTable[i] = 0;
		nodeArr[i] = 0;
	}
	
	fscanf(fp, "%c", &currChar);
	while(!feof(fp)) {
		populateTable(currChar);
		fscanf(fp, "%c", &currChar);	
	}

	printf("***PRINTING DATA TABLE***\n");
	for(int i = 0; i < 26; i++) {		//Use this to print dataTable
		printf("%c: ", (char) i+97);
		printf("%d\n", dataTable[i]);
	}

	for(int i = 0; i < 26; i++) {
		if(dataTable[i] > 0) {
			makeIndividualNodes(i);
		}
	}

	for(int i = 0; i < 26; i++) {		//Use this to print individual trees.
		if(nodeArr[i] == 0) {
			break;
		}
		displayNodes(nodeArr[i]);
	}

return 0;
}

void makeIndividualNodes(int tableIndex) {		//Makes individual Huffman Tree nodes
	HUFFNODE* temp = newHUFFNODE((char)tableIndex + 97, dataTable[tableIndex]);
	nodeArr[treeArrIndex] = temp;
	treeArrIndex++;
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

void populateTable(char currChar) {
	if(isalpha(currChar)) {
		int index = currChar - 97;
		dataTable[index]++;
	}
}
