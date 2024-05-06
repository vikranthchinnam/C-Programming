#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	for(int i = 1; i < argc; i++){
		if(strlen(argv[1]) != 5){
			puts("Bad!");
			exit(1);
		}
	}
	puts("Good!");

	return 0;
}
