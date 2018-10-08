//FIXME How to compress:

/*
1. Get the binary code from huffman tree.
2. Turn the 7 bits(Most significant bit is useless) into a number.
3. Then turn the number into a char using ASCII table and print it to the compressed file.
*/


//FIXME currently doesn't work with '\n'. Think of a way to fix this... maybe fgets?
//Compression software created by Aashman Gupta
//To include every character we need 95 elements

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "huffmanTree.h"

int dataTable[95];
HuffNode* nodeArr[95];
int treeArrIndex = 0;

void formHuffmanTree();
void populateTable(char currChar);
int getMinHuffNode();
void makeIndividualNodes(int index);
int setBit(int bitCode);
char* binStr = 0;						//String used in sevenDigitBuf
void sevenDigitBuff(char* str, FILE* fp);			//Func. to gather huffman codes. max length 7(so they can turn into ASCII)
int binToDec(char* str);

int main(int argc, char** argv) {
	char currChar;

	if (argc < 2) {
		printf("Type in a data file after ./a.out.\n");
		return 0;
	}

	char* dataFile = argv[argc - 1];
	
	FILE* fp = fopen(dataFile, "r");

	for (int i = 0; i < 95; i++) {		//This loop puts in initial values into 2D array.
		dataTable[i] = 0;
		nodeArr[i] = 0;
	}
	
	fscanf(fp, "%c", &currChar);		//This loop puts in the amount of repetitions of each character.
	while (!feof(fp)) {
		//printf("%c", currChar);
		populateTable(currChar);
		fscanf(fp, "%c", &currChar);	
	}
	
	fclose(fp);
	
	for (int i = 0; i < 95; i++) {		//Turns every character that was in the file to a huffmanNode.
		if(dataTable[i] > 0) {
			makeIndividualNodes(i);
		}
	}

	int flag = 0;						//Populates the array of all the HuffmanNodes.
	for (int i = 0; i < 95; i++) {
		if(nodeArr[i] != 0) {
			flag++;
		}
	}
	
	while(flag != 1) {					//This manipulates the huffman tree, and essentially creates the whole thing.
		formHuffmanTree();
		flag--;
	}

	HuffNode* finalTree = 0;

	for (int i = 0; i < 95; i++) {		//This is to get the final remaining node.
		if(nodeArr[i] != 0) {
			finalTree = nodeArr[i];
		}
	}
	
	findLeaves(finalTree, 0);
	char* codeTable[95];
	
	for (int i = 0; i < 95; i++) {		//Populates the code Table.
		codeTable[i] = returnCode(i);
	}

	FILE* fp2 = fopen(dataFile, "r");
	char* newFile = strcat(dataFile, ".compressed"); 
	FILE* compressedFile = fopen(newFile, "w");

	fprintf(compressedFile, "* ");
	for (int i = 0; i < 95; i++) {		//This puts in characters and there huffman code in to the compressed file, so that the data can be uncompressed.
		if (codeTable[i] != 0) {
			if(i == 0) {
				fprintf(compressedFile, "space%s ", codeTable[i]);
			}
			else {
				fprintf(compressedFile, "%c%s ", (char) i + 32, codeTable[i]);
			}
		}
	}
	fprintf(compressedFile, "/*\n");

	int codeTableIndex = 0;
	
	char* fullStr = malloc(sizeof(char) * 1000000);	//This will hold the whole compressed code that is created

	fscanf(fp2, "%c", &currChar);
	while ((!feof(fp2)) && (currChar != '\n')) {
		codeTableIndex = currChar - 32;
		//fprintf(compressedFile, "%s", codeTable[codeTableIndex]);
		strcat(fullStr, codeTable[codeTableIndex]);
		fscanf(fp2, "%c", &currChar);
	}
	printf("\n");

	sevenDigitBuff(fullStr, compressedFile);

	fclose(fp2);
	fclose(compressedFile);
	free(fullStr);

	return 0;
}

int binToDec(char* str) {
	int num = atoi(str);
	int rem, base = 1;
	int decVal = 0;

	while(num > 0) {
		rem = num % 10;
		decVal = decVal + rem * base;
		num = num / 10;
		base = base * 2;
	}
	return decVal;
}

void sevenDigitBuff(char* str, FILE* fp) {		//Groups code by 7 nums each
	int start = 0, count = 0;
	int end = 7;

	char* smallStr = malloc(sizeof(char) * 8);	//holds the smaller 7 digit string
	smallStr[8] = '\0';
	while(end <= strlen(str)) {
		smallStr = 0;
		smallStr = malloc(sizeof(char) * 8);
		for(int i = start; i < end; i++) {
			smallStr[count] = str[i];
			count++;
		}

		start = end;
		if(((end != strlen(str))) && (end < strlen(str)) && (end + 7 > strlen(str))) {
			end = strlen(str);
		}
		else {
			end = end + 7;
		}
		count = 0;
		//printf("%s", smallStr);
		//printf(" - The decimal is %d", binToDec(smallStr));
		//printf("- char is %c\n", binToDec(smallStr));
		fprintf(fp, "%c", binToDec(smallStr));
	}
}

int setBit(int bitCode) {
	int result;
	static char bits = 0;
	static int index = -1;
	
	if(index == -1) {
		index = 7;
	}
	
	if(bitCode == 1) {
		bits = (1UL << index) | bits;
	}

	result = (bits >> index) & 1;
	index--;
	printf("Byte: %c ", bits);
	return result;
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

// Makes individual Huffman Tree nodes
void makeIndividualNodes(int tableIndex) {
	HuffNode* temp = newHUFFNODE((char)tableIndex + 32, dataTable[tableIndex]);
	nodeArr[treeArrIndex] = temp;
	treeArrIndex++;
}

// Finds the current lowest occuring character 
int getMinHuffNode() {
	int min = 1000000;
	int retVal;

	for (int i = 0; i < 95; i++) {
		if (nodeArr[i] != 0) {
			if (getWeight(nodeArr[i]) < min) {
				min = getWeight(nodeArr[i]);
				retVal = i;
			}
		}
	}
	return retVal;
}

void populateTable(char currChar) {
	if ((currChar >= 32) && (currChar <= 126)) {
		int index = currChar - 32;
		dataTable[index]++;
	}
}
