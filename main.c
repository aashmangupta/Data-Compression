#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int dataTable[26];

void populateTable(char currChar);

int main(int argc, char** argv) {
	int count = 0;
	char currChar;

	if(argc < 2) {
		printf("Type in a data file after ./a.out.\n");
		return 0;
	}

	char* dataFile = argv[argc - 1];
	
	FILE* fp = fopen(dataFile, "r");
										//Make a loop so that characters get put in the place they belong in the alphabet.
	for(int i = 0; i < 26; i++) {		//This loop puts in initial value into 2D array.
		dataTable[i] = 0;
	}
	
	fscanf(fp, "%c", &currChar);
	while(!feof(fp)) {
		populateTable(currChar);
		fscanf(fp, "%c", &currChar);	
	}

/*	int j;								//used for printing out the dataTable.
	for(int i = 0; i < 26; i++) {
		j = i + 97;
		printf("%c ", (char)j);
		printf("%d ", dataTable[i]);
	}
	printf("\n");
*/
return 0;
}

void populateTable(char currChar) {
	if(isalpha(currChar)) {
		int index = currChar - 97;
		dataTable[index]++;
	}
}
