#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//end of name address is also passed in
void shortName(char *cp, char *endp, int n) {
	
	
	while(cp < endp){
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
	int n = atoi(argv[2]);
	char *endp = argv[1] + strlen(argv[1]);
		
	//code here!
	for(int i = 0; i < n; i++){
		shortName(argv[1] + i,endp , n);
	} 	
}
