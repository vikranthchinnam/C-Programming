#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	//argv[1] has your name.. split and output 2 names!
	char *input = argv[1];
	int len = strlen(input);

	//output the name for clone #1	
	// argv[1][i] <- --> input[i]
	char *cp = input;
	//CODE HERE!
	while (*cp) {
		putchar(*cp);
		cp++;
		if(!*cp)
			break;
		cp++;
	}
	printf("\n");
	cp = input+1;
	while(*cp){
		putchar(*cp);
		cp++;
		if(!*cp)
			break;
		cp++;
	}
	printf("\n");
}
