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
int print(){
	for(int i = 0; i < numPlayers; i++){
		printf("%s: %.2lf\n", names[i], balances[i]);
	}	
	return 0;
}
int main(int argc, char *argv[]) {
	//code here! use the following code just as reference 
	/*
	FILE *filep = fopen("gifts1.txt", "w");
	int n = 5; //let us assume players
	fprintf(filep, "%s %lf\n", names[0], balances[0]);
	fclose(filep);

	//when reading text data, we may not know how many players
	//you can read the following in a loop
	if (fscanf("%s%lf", names[i], &balances[i]) < 2)
		break;
	*/
	
//	FILE *filep = fopen("gifts1.txt", "w");
	
	int n = argc;
	numPlayers = n;
	if(strcmp(argv[1], "new") == 0){
		
		FILE *filep = fopen("gifts1.txt", "w");
		for(int i = 2; i < n; i += 2){
			strcpy(names[i-2], argv[i]);
			balances[i-2] = atof(argv[i + 1]);
			fprintf(filep, "%s %lf\n", names[i-2], balances[i-2]);
			
			printf("%s: %.2lf\n", names[i - 2], balances[i - 2]);
		}
		fclose(filep);
	}
	else{
		
		FILE *filep = fopen("gifts1.txt", "r+");
		int i = 0;
		while(i > -1){
			if(fscanf(filep, "%s %lf", names[i], &balances[i]) < 2){
				break;
			}
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
		FILE *filen = fopen("gifts1.txt", "w");
		for(int i = 0; i < numPlayers; i++){
			fprintf(filen, "%s %lf\n", names[i], balances[i]);
		}
		fclose(filen);
		print();
	}
	

}
