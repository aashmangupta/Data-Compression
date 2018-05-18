#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main(int argc, char** argv) {
	char* dataFile = argv[argc - 1];
	FILE* fp = fopen(dataFile, "r");
	
	char currChar;
	char* codeTable[26];
	int codeTableIndex;
	char temp[100000];

	for(int i = 0; i < 26; i++) {		//sets initial values of the codeTable to NULL.
		codeTable[i] = 0;
	}
	

	fscanf(fp, "%c", &currChar);		//Extracts all the code values.
	while(currChar != '*') {
		if(isalpha(currChar)) {
			codeTableIndex = currChar - 97;
			fscanf(fp, "%s", temp);
			codeTable[codeTableIndex] = malloc(strlen(temp) * sizeof(char));
			strcpy(codeTable[codeTableIndex], temp);
		}
		fscanf(fp, "%c", &currChar);
	}

	/*for(int i = 0; i < 26; i++) {		//Used for printing the code table.
		if(codeTable[i] != 0) {
			printf("%c %s\n", (char) (i + 97), codeTable[i]);
		}
	}*/

	char* codeInFile;
	char temp0;
	int count = 0;

	fscanf(fp, "%c", &temp0);
	while(!feof(fp)) {
		if(isalnum(temp0)) {
			codeInFile = realloc(codeInFile, sizeof(char) * (count + 1));
			codeInFile[count] = temp0;
			for(int i = 0; i < 26; i++) {
				if(codeTable[i] != 0) {
					printf("Comparing %s(%d) and %s(%d)\n", codeInFile, strlen(codeInFile), codeTable[i], strlen(codeTable[i]));
					if(strcmp(codeInFile, codeTable[i]) == 0) {
						printf("%c\n", (char) i +97);
						count = -1;
					}
				}
			}
			count++;
		}
		fscanf(fp, "%c", &temp0);
	}

	printf("%s\n", codeInFile);
	/*for(int i = 0; i < strlen(codeInFile); i++) {
		printf("%c", codeInFile[i]);
	}*/

return 0;
}
