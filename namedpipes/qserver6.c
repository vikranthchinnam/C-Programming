#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAXLEN 1000

int main() {
	char line[MAXLEN];

	//create a named pipe to read client's requests
	char publicfifo[MAXLEN];
	sprintf(publicfifo, "/tmp/%s-%d", getenv("USER"), getpid());
	mkfifo(publicfifo, 0600);
	chmod(publicfifo, 0622); //I can read & write, everyone else can only write!
	printf("Send your requests to %s\n", publicfifo);

	while (1) {
		FILE *fp = fopen(publicfifo, "r");
		if (!fp) {
			printf("FIFO %s cannot be opened for reading.\n", publicfifo);
			exit(2);
		}
		printf("Opened %s to read...\n", publicfifo);

		//wait for clients' requests
		while (fgets(line, MAXLEN, fp)) {

			char *cptr = strchr(line, '\n');
			if (cptr) 
				*cptr = '\0';
	
			//create a child to work with this client
			if (fork() == 0) {
				FILE *clientfp = fopen(line, "w");
				//create and send new server fifo to the client
				//for private one-on-one communcations
				char serverfifo[MAXLEN];
				sprintf(serverfifo, "/tmp/%s-%d", getenv("USER"), getpid());
				mkfifo(serverfifo, 0600);
				chmod(serverfifo, 0622);

				//send new server fifo name to the client
				fprintf(clientfp, "%s\n", serverfifo);
				fflush(clientfp);

				FILE *serverfp = fopen(serverfifo, "r");
				//read one line at a time from the client "5 17 8 15"
				//generate and send back running total
				char buffer[MAXLEN];
				int total=0;
				while (fgets(buffer, MAXLEN, serverfp)) {
					//tokenize and keep adding & outputting the running total
					//to the screen & also to the client
					char *tokenp = strtok(buffer, " ");
					while (tokenp) { //valid token?
						total += atoi(tokenp);
						printf("Total: %d\n", total);
						fprintf(clientfp, "Total: %d\n", total);
						fflush(clientfp);
						tokenp = strtok(NULL, " ");
					}
				}

				exit(0);
			}
		}
		fclose(fp);
	}
}
