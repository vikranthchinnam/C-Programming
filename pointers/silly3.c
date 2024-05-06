#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// cp[0], cp[2], cp[4],....
void shortName(char *cp) {
	//CODE HERE
	//!
	//
	while(*cp){
		putchar(*cp);
		cp++;
		if(!*cp){
			break;
		}
		cp++;

	}
	putchar('\n');
}


int main(int argc, char *argv[]) {
	//argv[1] has your name.. split and output 2 names!
	char *input = argv[1];

	//output the name for clone #1	
	shortName(input); // argv[1]

	//output the name for clone #2 ??
	shortName(input+1);
}
