#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>

#include <stdint.h>  
#include <inttypes.h>  
#include <pthread.h>
#include <errno.h>   
#include <fcntl.h>     
#define MAXLEN 1000
FILE* users[MAXLEN];
char dict[100000][MAXLEN];
int numWords;
int numUsers = 0;
void *child( void *ptr )
{
	FILE* clientfp = (FILE *) ptr;
	users[numUsers - 1] = clientfp;	
	char userName[20];
	sprintf(userName, "user%d", numUsers);
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
//	FILE *clientfp = fopen(line, "w");
	char serverfifo[MAXLEN];
	sprintf(serverfifo, "/tmp/%d", getpid() + rand());
	mkfifo(serverfifo, 0600);
	chmod(serverfifo, 0622);
				
				
//	fprintf(clientfp, "(Guess) Enter a letter in word %s > \n", guessWord);
	fprintf(clientfp, "%s\n", serverfifo);
	fflush(clientfp);
	fprintf(clientfp, "Welcome! \n\n");
	fflush(clientfp);
	FILE *serverfp = fopen(serverfifo, "r");
	char buffer[MAXLEN];
	char command[5];
	char list[5] = "list";
	char send[5] = "send";
	int misses = 0;
	char curr;
	char message[MAXLEN];
	while(fgets(buffer, MAXLEN, serverfp)){
		//curr = buffer[0];
//		fprintf(clientfp, "%s  %s \n", buffer, list);
//		fflush(clientfp);
		if(buffer[0] == '\n'){
			continue;
		}
		strncpy(command, buffer, 4);
		
		if(strcmp(command, list) == 0){
			for(int i = 1; i < numUsers + 1; i++){
				fprintf(clientfp, "user%d ", i);
			}
			fprintf(clientfp, "\n");
			fflush(clientfp);
		}
		else if(strcmp(command, send) == 0){
			strncpy(message, buffer + 9, MAXLEN);
			char *usernumber = strtok(message, " ");
			int userIndex = atoi(usernumber);
			if(--userIndex >= numUsers){
				fprintf(clientfp, "Sorry, user%d has not joined yet.\n", userIndex + 1);
				fflush(clientfp);
				continue;
			}
			strncpy(message, message + strlen(usernumber) + 1, MAXLEN);
			fprintf(users[userIndex], "%s says %s\n", userName, message);
			fflush(users[userIndex]);
			fprintf(clientfp, "Message sent!\n");
			fflush(clientfp);
		}
	}
}
int main(){
	char line[MAXLEN];
	
	srand(getpid());
	char publicfifo[MAXLEN];
	sprintf(publicfifo, "/tmp/vxc220016");
	mkfifo(publicfifo, 0600);
	chmod(publicfifo, 0622);
	printf("Send your requests to %s\n\n\n", publicfifo);

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
		
  			pthread_t thread1;
			numUsers++;
 							
			char userName[20];
			sprintf(userName, "user%d", numUsers);
			printf("%s joined! \n\n\n\n\n", userName);
			FILE *clientfp = fopen(line, "w");
			pthread_create(&thread1, NULL, child, (void *) clientfp);
		}
		fclose(fp);
	}

}
