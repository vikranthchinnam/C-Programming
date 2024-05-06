#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//skip n chars: cp[0], cp[n], cp[2*n], ...
// assume cp points to "sdgdfgdf\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0....":
void shortName(char *cp, int n) {
	//code here!
	
	while(*cp){
		putchar(*cp);
		cp += n;
		
	}
	putchar('\n');
	
}


int main(int argc, char *argv[]) {
	if (argc !=3) {
		fprintf(stderr, "Usage: %s <name> <# of clones>\n", argv[0]);
		exit(1);
	}
	//init buffer fully to '\0' chars
	char buffer[1024] = {};
	strcpy(buffer, argv[1]);

	int n = atoi(argv[2]);
	
	//code here!
	
	//code here!
	for(int i = 0; i < n; i++){
		shortName(buffer + i, n);
	} 	
}
