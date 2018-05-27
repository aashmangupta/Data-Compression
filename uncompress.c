//Uncompression software created by Aashman Gupta

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
	char* codeTable[95];
	int codeTableIndex;
	char temp[100000];

	for(int i = 0; i < 95; i++) {		//sets initial values of the codeTable to NULL.
		codeTable[i] = 0;
	}
	
	fscanf(fp, "%c", &currChar);
	if (currChar != '*') {
		printf("Wrong format data file. The data file should end with a \".compressed\"\n");
		return 0;
	}

	char letterCode[100];

	fscanf(fp, "%s", letterCode);
	while (strcmp(letterCode, "/*") != 0) {
		if ((letterCode[0] == 's') && (letterCode[1] == 'p')) {
			codeTableIndex = 0;
			memmove(letterCode, letterCode + 5, strlen(letterCode));
		}
		else {
			currChar = letterCode[0];
			codeTableIndex = currChar - 32;
			memmove(letterCode, letterCode + 1, strlen(letterCode));
		}
		codeTable[codeTableIndex] = malloc(strlen(letterCode) * sizeof(char));
		strcpy(codeTable[codeTableIndex], letterCode);
		fscanf(fp, "%s", letterCode);
	}

	char compressedCode[1000000];

	while (!isalnum(compressedCode[0])) {
		fgets(compressedCode, 1000000, fp);
	}

	int finish = 0, start = 0, result = 0;

	printf("Uncompressed text:\n");
	while (start < strlen(compressedCode)) {
		for (int i = 0; i < 95; i++) {
			if (codeTable[i] != 0) {
				result = strComp(codeTable[i], compressedCode, start, finish);
				if (result == 1) {
					printf("%c", (char) i + 32);
					start = finish + 1;
					i = 95;
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





