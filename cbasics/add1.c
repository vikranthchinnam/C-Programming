#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	int number = 0;
	for(int i = 1; i < argc; i++){
		number = number + atoi(argv[i]);
	}
	printf("The sume is : %d\n", number);
}
