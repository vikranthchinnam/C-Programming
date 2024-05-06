#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//skip n chars: cp[0], cp[n], cp[2*n], ...
void shortName(char *cp, int n) {
	//code here!
	while(*cp){
		putchar(*cp);
		for(int i = 1; i <= n;i++){
			cp++;
			if(!*cp){
				break;
			}
		}
	}
	putchar('\n');
}

int main(int argc, char *argv[]) {
	if (argc !=3) {
		fprintf(stderr, "Usage: %s <name> <# of clones>\n", argv[0]);
		exit(1);
	}
	char *input = argv[1];
	int n = atoi(argv[2]);
	
	//code here!
	for(int i = 0; i < n; i++){
		shortName(input + i, n);
	} 	
}
