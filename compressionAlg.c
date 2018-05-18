#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "huffmanTree.h"

int dataTable[26];
HuffNode* nodeArr[26];
int treeArrIndex = 0;

void formHuffmanTree();
void populateTable(char currChar);
int getMinHuffNode();
void makeIndividualNodes(int index);

int main(int argc, char** argv) {
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
	
	fscanf(fp, "%c", &currChar);		//This loop puts in the amount of repetitions of each character.
	while(!feof(fp)) {
		populateTable(currChar);
		fscanf(fp, "%c", &currChar);	
	}
	
	fclose(fp);
	
	for(int i = 0; i < 26; i++) {		//Turns every character that was in the file to a huffmanNode.
		if(dataTable[i] > 0) {
			makeIndividualNodes(i);
		}
	}

	int flag = 0;						//Populates the array of all the HuffmanNodes.
	for(int i = 0; i < 26; i++) {
		if(nodeArr[i] != 0) {
			flag++;
		}
	}
	
	while(flag != 1) {					//This manipulates the huffman tree, and essentially creates the whole thing.
		formHuffmanTree();
		flag--;
	}

	HuffNode* finalTree = 0;

	for(int i = 0; i < 26; i++) {		//This is to get the final remaining node.
		if(nodeArr[i] != 0) {
			finalTree = nodeArr[i];
		}
	}
	
	findLeaves(finalTree, 0);
	char* codeTable[26];
	
	for(int i = 0; i < 26; i++) {		//Populates the code Table.
		codeTable[i] = returnCode(i);
	}

	FILE* fp2 = fopen(dataFile, "r");
	char* newFile = strcat(dataFile, ".compressed"); 
	FILE* compressedFile = fopen(newFile, "w");

	for(int i = 0; i < 26; i++) {		//This puts in code values in to the compressed file, so that the data can be uncompressed.
		if(codeTable[i] != 0) {
			fprintf(compressedFile, "%c%s ", (char) i + 97, codeTable[i]);
		}
	}
	fprintf(compressedFile, "*\n");

	int codeTableIndex = 0;
	
	fscanf(fp2, "%c", &currChar);
	while((!feof(fp2)) && (currChar != '\n')) {
		codeTableIndex = currChar - 97;
		fprintf(compressedFile, "%s", codeTable[codeTableIndex]);
		fscanf(fp2, "%c", &currChar);
	}

	fclose(fp2);
	fclose(compressedFile);

return 0;
}

void formHuffmanTree() {
	int temp1Index = getMinHuffNode();
	HuffNode* temp1 = nodeArr[temp1Index];
	nodeArr[temp1Index] = 0;

	int temp2Index = getMinHuffNode();
	HuffNode* temp2 = nodeArr[temp2Index];

	HuffNode* resultingNode = newHUFFNODE(0, getWeight(temp1) + getWeight(temp2));
	nodeArr[temp2Index] = resultingNode;

	setLeft(resultingNode, temp1);
	setParent(temp1, resultingNode);
	setRight(resultingNode, temp2);
	setParent(temp2, resultingNode);
	setParent(resultingNode, 0);
}

void makeIndividualNodes(int tableIndex) {		//Makes individual Huffman Tree nodes
	HuffNode* temp = newHUFFNODE((char)tableIndex + 97, dataTable[tableIndex]);
	nodeArr[treeArrIndex] = temp;
	treeArrIndex++;
}

int getMinHuffNode() {							//Finds the current lowest occuring character 
	int min = 1000000;
	int retVal;

	for(int i = 0; i < 26; i++) {
		if(nodeArr[i] != 0) {
			if(getWeight(nodeArr[i]) < min) {
				min = getWeight(nodeArr[i]);
				retVal = i;
			}
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
