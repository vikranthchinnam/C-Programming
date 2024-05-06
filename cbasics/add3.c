#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
	char line[100];
	fgets(line, 100, stdin);

	int total = 0;
	char *tokenp = strtok(line, " ");
	while(tokenp) {
		total += atoi(tokenp);
		tokenp = strtok(NULL, " ");
	}
	printf("The sume is : %d\n", total);
}
