#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//Usage example: operators 5 2 10 7 6 
//Output from one process should be 5 - 2 + 10 - 7 = 6
int main(int argc, char *argv[]) {

	int operatorCount = argc - 3; //tool, output, last operand
	char operators[operatorCount];
	int result = atoi(argv[1]);  //initialize result
	for(int i=0; i<operatorCount; i++) {
		operators[i] = '+';
		if (fork()) {
			//do the operation and proceed...
			result += atoi(argv[i+2]);
			continue; //go back to for loop - next level
		}
		operators[i] = '-';
		if (fork()) {
			//do the operation and proceed...
			result -= atoi(argv[i+2]);
			continue;
		}

		operators[i] = '*';
		if (fork()) {
			//do the operation and proceed...
			result *= atoi(argv[i+2]);
			continue;
		}

		operators[i] = '/';
		result /= atoi(argv[i+2]);
	}

	if (result == atoi(argv[argc-1])) {
		for(int i=0; i<operatorCount; i++)
			printf("%s %c ", argv[i+1], operators[i]);
		printf("%s = %s\n", argv[argc-2], argv[argc-1]);
	}
	for(int i=0; i<4*operatorCount; i++)
		wait(NULL);
}
