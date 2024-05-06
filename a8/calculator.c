#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLEN 1000

char operators[100];
int fds[201][2];
int operatorCount=0;
int numPipes=0;

void child(int index) { // operators[index] specifies the operator for this child
	//CODE HERE!
	//reconfigure appropriate pipes (plumbing) to fds 0, 3 and 1
	// mysum: 0, 1, 2 --> 2*index, 2*index+1, 2*index+2
	//close all pipes! IF missed, you will end up with lot of orphans! 
	// operators[index] +         -        *            /
	// execl            add       subtract multiply    divide
	//printf() is bad idea! --> fprintf(stderr, "...\n",
	
	//rewire first pipe read to fd 0
	dup2(fds[2*index][0], 0); //equivalent to close(0); dup(fds[0][0]); 
	//rewire second pipe read to fd 3
	dup2(fds[2*index+1][0], 3); //equivalent to close(3); dup(fds[1][0]);
	//rewire third pipe write to fd 1
	dup2(fds[2*index+2][1], 1); //equivalent to close(1); dup(fds[2][1]);
		
	for(int i=0; i<numPipes; i++) {
		close(fds[i][0]); close(fds[i][1]);
	}
	
	if(operators[index] == '+'){
		execl("./add", "add", "-v", NULL);  //any argument will enable debug messages
	}
	else if (operators[index] == '-'){
		execl("./subtract", "subtract", "-v", NULL);
	}
	else if(operators[index] == '*'){
		execl("./multiply","multiply", "-v", NULL);
	}
	else if(operators[index] == '/'){
		execl("./divide","divide", "-v", NULL);
	}
	else{
		fprintf(stderr, "operator doesn't exist...\n");
	}
	//fprintf(stderr, "the world is ending...\n");
}

int main(int argc, char *argv[]) {
	char line[MAXLEN], *temp;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	FILE *dataFile = fopen(argv[1], "r");
	//read the first line - it contains the configuration
	fgets(line, MAXLEN, dataFile); 

	// sample content for line: a + b - c
	strtok(line, " \n"); //skip the symbol representing variable/parameter
	while (temp = strtok(NULL, " \n")) {
		operators[operatorCount] = temp[0];
		//printf("operator: %c\n", operators[operatorCount]);
		operatorCount++;
		strtok(NULL, " \n"); //skip the symbol representing variable/parameter
	}

	//create the necessary # of pipes
	numPipes = operatorCount * 2 + 1;

	//CODE HERE!
	//loop: create that many pipes (numPipes) -- all pipes are created!
	for(int i = 0; i < numPipes; i++){
		pipe(fds[i]);
	}	
	//loop: create that many children (operatorCount) - each one invokes child(i)
	for(int i = 0; i < operatorCount; i++){
		if(!fork())
			child(i);
	}	

	//proceed to read data from the file and keep pumping them into pipes and read result 
	//while (fscanf(dataFile, "%d", &value) > 0)
	//  write it to first pipe
	//	use loop to read remaining data in that line & keep pumping to pipes: for i --> pipe 2*i+1 
	//	read the final result from the final pipe (numPipes-1) & print
	int i = -1;
	int result, value;
	while(fscanf(dataFile, "%d", &value) > 0){
		if(i == -1){
			write(fds[i+1][1], &value,sizeof(int));
		}
		else if(i == 0){
			write(fds[i+1][1], &value, sizeof(int));
		}
		else{
			write(fds[(2*i)+1][1], &value, sizeof(int));
		}
		i++;
		if(2*i == numPipes-1){
			read(fds[2*i][0], &result,sizeof(int));
			printf("%d\n", result);
			i = -1;
		}
	}

}

