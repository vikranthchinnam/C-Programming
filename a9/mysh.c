#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

//read all the quotes from quotes.txt
//when client asks for a motivational quote, select one randomly and send it out.

#define MAXQUOTES 10000
#define MAXLEN 1000

char *quotes[MAXQUOTES];
int numQuotes=0;
char *commands[201];
int fds[201][2];
int numPipes = 0;
//runs a simple command
//cmdname arg1 arg2 arg3 ...
void runCommand(char *command) {
	//split and assemble the arguments and invoke execvp()
	//use strtok(..)
	
	char *arguments[MAXLEN];
	char *tool = strtok(command, " \n");
	arguments[0] = tool;

	int i=1;
	//keep getting tokens (individual words)
	while ((arguments[i] = strtok(NULL, " \n")) != NULL)
		i++;
	
	execvp(tool, arguments);
	fputs("I hope you don't see me!\n", stderr);
}

//cmd0 | cmd1 | cmd2 | cmd3 | cmd4 ....
void child(int i) {
	//rewire pipes to 0 and 1 
	
	//rewire first pipe read to fd 0
	if(i > 0){
		dup2(fds[i-1][0], 0); //equivalent to close(0); dup(fds[0][0]); 
	}
	//rewire second pipe read to fd 3
	//dup2(fds[2*i+1][0], 3); //equivalent to close(3); dup(fds[1][0]);
	//rewire third pipe write to fd 1
	if(i < numPipes - 1){
		dup2(fds[i][1], 1); //equivalent to close(1); dup(fds[2][1]);
	}
	//do NOT rewire 0 for the first command - leave it as std input
	//do NOT rewrite 1 for the last command - leave it as std output
	//close unnecessary pipes - for loop?
	for(int i=0; i<numPipes; i++) {
		close(fds[i][0]); close(fds[i][1]); 
	}
	//run ith command
	runCommand(commands[i]);
}

void processLine(char *line) {
	char *pipePtr = strchr(line, '|'); //does this command have | chars?
	char *equalPtr = strchr(line, '='); //does this command have =?
	if (pipePtr) { //not NULL - cmd1 | cmd2 | cmd3 ....
//		command has several sub-commands connected with pipes
//		setup commands array
//		setup pipes array
//		fork & create children --> invoke child(i) in a loop
		//cmd0 | cmd1 | cmd2 | cmd3 | cmd4 
		// invoke child(i) for the last command directly?
		char *command = strtok(line, "|");
		commands[0] = command;
		int i = 1;
		while((commands[i] = strtok(NULL, "|")) != NULL)
			i++;
				
		numPipes = i;

		//CODE HERE!
		//loop: create that many pipes (numPipes) -- all pipes are created!
		for(int i = 0; i < numPipes; i++){
			pipe(fds[i]);
		}	
		//loop: create that many children (operatorCount) - each one invokes child(i)
		for(int i = 0; i < numPipes; i++){
			if(i != numPipes - 1){
				if(!fork())
					child(i);
			}
			else{
				dup2(fds[i-1][0],0);

				for(int j=0; j<numPipes; j++) {
					close(fds[j][0]); close(fds[j][1]); 
				}
				runCommand(commands[i]);
			}
		}	



		
	} else if (equalPtr) { 
		//command has = operator, so 2 commands --> 2 processes
		
		char *command1 = strtok(line, "=");
		char *command2 = strtok(NULL, "\n");

		//create 2 pipes
		int toparent[2], tochild[2];
		pipe(toparent);
		pipe(tochild);
		//fork()
		//reconfigure pipes for 0 and 1
		//runCommand()
		if (fork()) {
			dup2(toparent[0], 0); //read from child: toparent[0]
			dup2(tochild[1],  1); //write to child: tochild[1]
			close(toparent[0]); close(toparent[1]);
			close(tochild[0]); close(tochild[1]);
			runCommand(command1);
		} else {
			dup2(tochild[0], 0); //read from parent: tochild[0]
			dup2(toparent[1], 1); //write to parent: toparent[1]
			close(toparent[0]); close(toparent[1]);
			close(tochild[0]); close(tochild[1]);
			runCommand(command2);
		}
   	 } else 
		//it is a simple command, no pipe or = character
		runCommand(line);

	exit(0);
}

int main() {
	// load up all the quotes from quotes.txt - look at quoteserver.c for the code
	
	char line[MAXLEN];

	FILE *fp = fopen("quotes.txt", "r");
	if (!fp) {
		puts("quotes.txt cannot be opened for reading.");
		exit(1);
	}
	int i=0;

	//read one line at a time, allocate memory, then copy the line into array
	while (fgets(line, MAXLEN, fp)) {
		quotes[i] = (char *) malloc (strlen(line)+1);
		strcpy(quotes[i], line);
		i++;
	}
	numQuotes = i;

	srand(getpid() + time(NULL) + getuid());

	// infinite loop to serve the customer
	srand(time(NULL));
	while (1) {
		//output a random quote to stderr
		fputs(quotes[rand()%numQuotes], stderr);
		fprintf(stderr, "# "); //show prompt to the user
		//get the user input -- command line
		fgets(line, 1000, stdin);

		//spawn a child for taking care of it
		if (fork() == 0) 
			processLine(line);

		//wait the child to finish the job!
		wait(NULL);
	}
}
