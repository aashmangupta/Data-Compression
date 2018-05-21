#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int strComp(char* codeTableStr, char* fullCompressedStr, int start, int finish);

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Type in a data file after ./a.out.\n");
		return 0;
	}
	
	char* dataFile = argv[argc - 1];
	FILE* fp = fopen(dataFile, "r");

	char currChar;
	char* codeTable[26];
	int codeTableIndex;
	char temp[100000];

	for(int i = 0; i < 26; i++) {		//sets initial values of the codeTable to NULL.
		codeTable[i] = 0;
	}
	
	fscanf(fp, "%c", &currChar);

	if(currChar != '*') {
		printf("Wrong format data file. The data file should end with a \".compressed\"\n");
		return 0;
	}

	fscanf(fp, "%c", &currChar);		//Extracts all the code values.
	while (currChar != '*') {
		if (isalpha(currChar)) {
			codeTableIndex = currChar - 97;
			fscanf(fp, "%s", temp);
			codeTable[codeTableIndex] = malloc(strlen(temp) * sizeof(char));
			strcpy(codeTable[codeTableIndex], temp);
		}
		fscanf(fp, "%c", &currChar);
	}

	char compressedCode[1000000];

	while (!isalnum(compressedCode[0])) {
		fgets(compressedCode, 1000000, fp);
	}

	int finish = 0, start = 0, result = 0;

	printf("Uncompressed text:\n");
	while (start < strlen(compressedCode)) {
		for (int i = 0; i < 26; i++) {
			if (codeTable[i] != 0) {
				result = strComp(codeTable[i], compressedCode, start, finish);
				if (result == 1) {
					printf("%c", (char) i + 97);
					start = finish + 1;
					i = 26;
				}
			}
		}
		finish++;
	}
	printf("\n");
	
	fclose(fp);

	return 0;
}

int strComp(char* codeTableStr, char* fullCompressedStr, int start, int finish) {
	if (strlen(codeTableStr) != ((finish + 1) - start)) {
		return 0;
	}
	int count = 0;
	for (int i = start; i <= finish; i++) {
		if (codeTableStr[count] != fullCompressedStr[i]) {
			return 0;
		}
		count++;
	}
	return 1;
}





