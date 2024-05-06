#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>
#define MAXLEN 1000
void pexit(char *errmsg) {
	fprintf(stderr, "%s\n", errmsg);
	exit(1);
}
char dict[100000][MAXLEN];
int main(int argc, char *argv[])
{
//	char line[MAXLEN];
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
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char buffer[1025];
    time_t ticks; 

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		pexit("socket() error.");
		
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(buffer, '0', sizeof(buffer)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int port = 4999;
//	int port = atoi(argv[1])-1;
	do {
		port++;
    	serv_addr.sin_port = htons(port); 
    } while (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0);
	printf("bind() succeeds for port #%d\n", port);

    if (listen(listenfd, 10) < 0)
		pexit("listen() error.");

	int counter=0;
    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
		counter++;
		//to serve multiple clients in parallel, fork() and create a child process
		//to work with each client.
		if (fork())
			continue;
		//read a line from client - use a buffer - read(connfd, ...
		char command[1025];
		int n;
		printf("serving client %d.\n", counter);
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
		n = sprintf(buffer, "(Guess) Enter a letter in word %s > ", guessWord);
		write(connfd,buffer, n);
		char curr;
		int misses = 0;
		while ((n = read(connfd, command, 1024)) > 0) {
			command[1] = '\0'; // add \0 to indicate end of command
			curr = command[0];
			bool missed = true;
			for(int i = 0; i < currWordLength; i++){
				if(guessWord[i] == curr){
					n = sprintf(buffer, "%c is already in the word \n", curr);
					write(connfd,buffer, n);
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
				n = sprintf(buffer, "the word is %s. You missed %d times \n", guessWord,misses);
				write(connfd,buffer, n);
				break;
			}
			else{
				if(missed){
					misses++;
					n = sprintf(buffer, "%c is not in the word \n", curr);
					write(connfd,buffer, n);
				}
				n = sprintf(buffer, "(Guess) Enter a letter in word %s > ", guessWord);
				write(connfd,buffer, n);
			}
			//use buffer instead of "ls -l" 
		//	FILE *fcommand = popen(command, "r");
			
			//get the output of that command and forward it to client
		//	while ((n = fread(buffer, 1, sizeof(buffer), fcommand)) > 0)
        	//	write(connfd, buffer, n); 
								
		//	pclose(fcommand);
		}
        	close(connfd);
		exit(1);
     }
}
