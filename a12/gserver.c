/*
 * read dictionary file to array of words & get ready to play the hangman!
if you are using fgets() to read the word
	  cptr = strchr(line, '\n');
	  if (cptr)
	  	*cptr = '\0';
 However, since we are dealing with words, you can use fscanf(...,"%s", ...) instead!

 * wait for a request to come in (client specifies unique pipename)
 * select a random word using rand()
 * fork() to create a child to handle this client! (dedicated server process for that client)
 * fork() enables games to proceed in parallel. Parent returns to wait for new client requests
 * respond with another unique server-side pipename 
 *
 * send a bunch of stars (indicating the word length)
 * for each guess the client sends in, respond with a message 
 * and send updated display word.
 *
 * Whenever you send strings through named pipes, 
 * terminate with '\n' and also do fflush() for that data to make it to other side without getting stuck
 * in buffers.
 *
 * open public fifo
 * while (fgets()) {
 * }
 *
 *


srand(....);

wait for a client connection
rand() to select a word
fork()
	child process:

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#define MAXLEN 1000

char dict[100000][MAXLEN];
int main(){
	char line[MAXLEN];
	FILE *words;
	words = fopen("dictionary.txt", "r");
	if(NULL == words){
		printf("file can't be openedi \n");
		exit(2);
	}
	int numWords = 0;
	while(fgets(dict[numWords], MAXLEN, words) != NULL){
		numWords++;
	}
	
	
	char publicfifo[MAXLEN];
	sprintf(publicfifo, "/tmp/vxc220016");
	mkfifo(publicfifo, 0600);
	chmod(publicfifo, 0622);
	printf("Send your requests to %s\n", publicfifo);

	while(1){
		FILE *fp = fopen(publicfifo, "r");
		if(!fp){
			printf("FIFO %s cannot be opened for reading.\n", publicfifo);
			exit(2);
		}
		
		while(fgets(line, MAXLEN, fp)){
			char *cptr = strchr(line, '\n');
			if(cptr)
				*cptr = '\0';

			if(fork() == 0){
				srand(getpid());
				int wordIndex = rand() % (numWords - 1);
				int currWordLength = strlen(dict[wordIndex]);
				int lettersRemaining = currWordLength - 1;
				char currWord[currWordLength];
				char guessWord[currWordLength];
				for(int i = 0; i < currWordLength - 1; i++){
					guessWord[i] = '*';
					currWord[i] = dict[wordIndex][i];
				}
				guessWord[currWordLength - 1] = '\0';
				FILE *clientfp = fopen(line, "w");
				char serverfifo[MAXLEN];
				sprintf(serverfifo, "/tmp/%d", getpid());
				mkfifo(serverfifo, 0600);
				chmod(serverfifo, 0622);
				
				
				
				fprintf(clientfp, "%s\n", serverfifo);
				fflush(clientfp);
				fprintf(clientfp, "(Guess) Enter a letter in word %s > \n", guessWord);
				fflush(clientfp);
				FILE *serverfp = fopen(serverfifo, "r");
				char buffer[MAXLEN];
				char curr;
				int misses = 0;
				fprintf(stderr, "writing to %s via %s using the wordle %s \n", line, serverfifo, currWord);
				while(fgets(buffer, MAXLEN, serverfp)){
					curr = buffer[0];
					
					bool missed = true;
					for(int i = 0; i < currWordLength; i++){
						if(guessWord[i] == curr){
							fprintf(clientfp,"%c is already in the word \n", curr);
							fflush(clientfp);
							missed = false;
							break;
						}
						if(currWord[i] == curr){
							lettersRemaining--;
							guessWord[i] = curr;
							missed = false;	
						}
					}
					if(lettersRemaining <= 0){
						fprintf(clientfp, "The word is %s. You missed %d times \n", guessWord, misses);
						break;
					}else{
						if(missed){
							misses++;
							fprintf(clientfp, "%c is not in the word \n", curr);
							fflush(clientfp);
						}
						fprintf(clientfp, "(Guess) Enter a letter in word %s > \n", guessWord);
						fflush(clientfp);
					}
				}
				exit(0);
			}
		}
		fclose(fp);
	}

}
