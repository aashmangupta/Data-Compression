#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, char** argv) {
	if(argc < 1) {
		printf("Type in a data file after ./a.out.\n");
		return 0;
	}

	char* dataFile = argv[argc - 1];
	
	FILE* fp = fopen(dataFile, "r");
	char currChar[30][1];				//make a loop so that characters get put in the place they belong in the alphabet.
	int count = 0;

	fscanf(fp, "%c", &currChar[0][0]);
	
	while(!feof(fp)) {
		currChar = tolower(currChar[count][0]);
		
		if() {

		}

		printf("%c", currChar);
		fscanf(fp, "%c", &currChar);	
		//find the character and incerement its frequency in the array
	}

return 0;
}
