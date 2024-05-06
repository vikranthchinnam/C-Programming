/* make up unique pipename for client
 * send it to the server (public pipe)
 * get another unique pipename from the server
 * repeat
 * 	read a line including starred word from the client pipe
 *  display that line to the user 
 *  check whether game is over?
 *  get the user's guess letter
 *  send to the server using server pipe
 */

// custom client for this specific server
/*
while (1)
	read a line from server // if read fails, break;
	// fgets() returns NULL when it fails
	if that line contains "Enter a" // strstr(line, "Enter a")
		char *cptr = strchr(line, '\n');
		if (cptr)
			*cptr = '\0';
		printf(line);
		char response[100];
		scanf("%s", response);
		
		//send one char to server
		fprintf(serverfp, "%c\n", response[0]);
		fflush(serverfp);
	else
		printf(line);
		if line contains "The word is"
			break;

unlink(...);
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAXLEN 1000

int main(int argc, char *argv[]) {	
	if (argc !=2) {
		puts("Usage: qclient <server-fifo-name>");
		exit(1);
	}

	// argv[1] is the server fifo name

	char clientfifo[MAXLEN];
	sprintf(clientfifo, "/tmp/%s-%d", getenv("USER"), getpid());
	mkfifo(clientfifo, 0600);
	chmod(clientfifo, 0622);
	
	//open argv[1] for writing, send clientfifo
	FILE *fp = fopen(argv[1], "w");

	//fputs(clientfifo, fp);
	//add \n after clientfifo to avoid potential race conditions in server
	fprintf(fp, "%s\n", clientfifo);
	fclose(fp);

	//open clientfifo for reading and read the quote & print in the screen - improve your life! :-)
	FILE *clientfp = fopen(clientfifo, "r");
	//read the new server-fifo, then open it for writing! as serverfp
	char serverfifo[MAXLEN];
	//fgets(serverfifo, clientfp); -- fscanf() is better! No need to worry about \n
	fscanf(clientfp, "%s", serverfifo);
	char line[MAXLEN];
	fgets(line, MAXLEN, clientfp); //get rid of \n
	FILE *serverfp = fopen(serverfifo, "w");
//	if(fork()){
	while (1){
	//	read a line from server // if read fails, break;
		if(fgets(line, MAXLEN, clientfp)){
			if(strstr(line, "Enter a")){
				char *cptr = strchr(line, '\n');
				if(cptr)
					*cptr = '\0';
				printf(line);
				char response[MAXLEN];
			//	fgets(line, MAXLEN, stdin);
				scanf("%s", response);
			//	printf("%s", response);
			//	char resp = response[0];
				fprintf(serverfp, "%c\n", response[0]);
				fflush(serverfp);
			}
			else{
				printf("\t");
				printf(line);
				if(strstr(line, "The word is")){
					break;
				}
			}
		}
	// fgets() returns NULL when it fails
	}
//	}
	/*if (fork()) 
		//parent - responsible for getting user input and sending to server
		while(1) {
			//get the user input - one line at a time and send it to server.
			fgets(line, MAXLEN, stdin);
		
			//send that line to server
			//to avoid output getting stuck in the local buffer,
			//we need 2 things: \n and fflush()
			fprintf(serverfp, "%s\n", line);
			fflush(serverfp);
		}
	else 
		//child - responsible for getting responses from server and displaying
		while (1) {
			fgets(line, MAXLEN, clientfp);
			puts(line);
		}

*/

	unlink(clientfifo);
}
