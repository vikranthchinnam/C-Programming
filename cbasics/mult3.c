#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	srand(time(NULL) + getpid());
	int number = rand() % 1000 + 1;

	for(int i = 1; i <= 10; i++){
		printf("%3d * %3d = %5d\n", i, number, i*number);
	} 
}
