#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

char dataTable[26][2];

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
		currChar = i;					//FIXME... Can't I just use a single array?
		printf("%c", currChar);			//FIXME problem with converting to ASCII and back
		dataTable[i][0] = currChar;		//...Refer to index through ASCII values...
		dataTable[i][1] = 0;
	}
	
	fscanf(fp, "%c", &currChar);
	while(!feof(fp)) {
		populateTable(currChar);
		fscanf(fp, "%c", &currChar);	
	}

	for(int i = 0; i < 26; i++) {
		printf("%c", dataTable[i][0]);
		printf(": %c", dataTable[i][1]);
	}
	printf("\n");

return 0;
}

void populateTable(char currChar) {
	//int index = currChar - 97;
	//int oldFreq = dataTable[index][1];

	//dataTable[index][1] = oldFreq++;
}
