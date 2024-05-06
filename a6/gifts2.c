#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//let us assume that there will not be more than 100 players
#define MAXPLAYERS 100
//let us assume that max length for any name is 100 characters
#define MAXLEN 100

//arrays to store the player names and balances
char names[MAXPLAYERS][MAXLEN];
double balances[MAXPLAYERS];
int numPlayers = 0; //set when actual player data is loaded

//search the player names array and return the index if specified name is found
//return -1 otherwise.
int findIndex(char *name) {
        for(int i=0; i<numPlayers; i++)
            if(strcmp(name, names[i]) == 0)
               return i;

        return -1;
}

// use binary data file gifts2.dat to read and store the results.

int main(int argc, char *argv[]) {
	//code here!
	//following line makes sense only for writing to file
	//int fd = open("gifts2.dat", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	//if the command is not "new",
	//int fd = open("gifts2.dat", O_RDONLY);

	//how to write and read individual name?
	//simplest approach is to write the name length first, then the actual content
	//to make reading the name from file easier.
	//write(fd, balances, sizeof(double));
	//close(fd);
	//
		
	
	int n = argc;
	numPlayers = n;
	if(strcmp(argv[1], "new") == 0){
		
		int fd = open("gifts2.dat", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
		for(int i = 2; i < n; i += 2){
			strcpy(names[i-2], argv[i]);
			balances[i-2] = atof(argv[i + 1]);
			int length = strlen(names[i-2]) + 1;
			write(fd, &length, sizeof(int));
			write(fd, &names[i-2], length);
			write(fd, &balances[i-2], sizeof(double));
			printf("%s: %.2lf\n", names[i - 2], balances[i - 2]);
		}
		close(fd);
	}
	else{
		
		int fd = open("gifts2.dat", O_RDONLY);
		int i = 0;
		while(i > -1){
			int *length = (int*) malloc(sizeof(int));
			int size = read(fd, length, sizeof(int));
			
			if(size == 4){
				read(fd, &names[i], *length);
				read(fd, &balances[i], sizeof(double));
			}
			else
				break;
			i++;
		}
		numPlayers = i;
		int giver = findIndex(argv[1]);
		double amount = atof(argv[2]);
		balances[giver] = balances[giver] - amount;
		amount = amount / (argc - 3);
		for(int i = 3; i < n; i++){
			int reciever = findIndex(argv[i]);
			balances[reciever] = balances[reciever] + amount;
		}
		int filen = open("gifts2.dat", O_WRONLY);
		for(int i = 0; i < numPlayers; i++){
			
			int length = strlen(names[i]) + 1;
			write(filen, &length, sizeof(int));
			write(filen, &names[i], length);
			write(filen, &balances[i], sizeof(double));
			printf("%s: %.2lf\n", names[i], balances[i]);
		}
		close(filen);
	}
}
