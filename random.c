#include<stdio.h>
#include<stdlib.h>

int main() {

	int num = 0;

	FILE* fp = fopen("data", "w");

	for(int i = 0; i < 100000; i++) {
		num = (rand() % (122- 97 + 1)) + 97;
		fprintf(fp, "%c", (char)num);
	}

	fclose(fp);
return 0;
}
