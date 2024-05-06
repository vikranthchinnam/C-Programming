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

struct Player {
	char name[MAXLEN];
	double balance;
} ;

//struct is like class - we can use an array of struct (we can use like an array of objects).
struct Player players[MAXPLAYERS];
int numPlayers = 0; //set when actual player data is loaded

//search the player names array and return the index if specified name is found
//return -1 otherwise.
int findIndex(char *name) {
        for(int i=0; i<numPlayers; i++)
            if(strcmp(name, players[i].name) == 0)
               return i;

        return -1;
}

// use binary data file gifts2.dat to read and store the results.

int main(int argc, char *argv[]) {
	//code here!
	
	int n = argc;
	numPlayers = n;
	if(strcmp(argv[1], "new") == 0){
		int j = 0;
		for(int i = 2; i < n; i += 2){
			char name[100];
			strcpy(name, argv[i]);
			double balance = atof(argv[i + 1]);
			struct Player temp;
			strcpy(temp.name, name);
			temp.balance = balance;
			players[j] = temp;
			printf("%s: %.2lf\n", players[j].name, players[j].balance);
			j++;
		}

		//writing data - array of Struct - just one fwrite()
		FILE *filep = fopen("gifts3.dat", "wb"); //for writing
		fwrite(players, sizeof(struct Player), numPlayers, filep);
		fclose(filep);

	}
	else{
		
		//reading data - array of Struct - just one fread()
		FILE *filep = fopen("gifts3.dat", "rb"); //for reading
		numPlayers = fread(players, sizeof(struct Player), MAXPLAYERS, filep);
		fclose(filep);
		numPlayers = MAXPLAYERS;
		//printf("%d", findIndex(argv[1]));
		int giver = findIndex(argv[1]);
		double amount = atof(argv[2]);
		players[giver].balance = players[giver].balance - amount;
		amount = amount / (argc - 3);
		for(int i = 3; i < n; i++){
			int reciever = findIndex(argv[i]);
			players[reciever].balance = players[reciever].balance + amount;
		}
		int i = 0;
		while(strlen(players[i].name) > 0){
			printf("%s: %.2lf\n", players[i].name, players[i].balance);
			i++;
		}
		//writing data - array of Struct - just one fwrite()
		filep = fopen("gifts3.dat", "wb"); //for writing
		fwrite(players, sizeof(struct Player), numPlayers, filep);
		fclose(filep);
	}
}
