//Usage: quoteclient <server-fifo-filename>
//
//create own named pipe (fifo) and set permissions
//send this fifo name to server
//open own named pipe
//read the quote and display

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

	// come up with client fifo name, so that server can respond.
    char clientfifo[MAXLEN];
	sprintf(clientfifo, "/tmp/%s-%d", getenv("USER"), getpid());
	mkfifo(clientfifo, 0600);
	chmod(clientfifo, 0622);
	
	//open argv[1] for writing, send clientfifo
	FILE *fp = fopen(argv[1], "w");
	if (!fp) {
		printf("Cannot open %s for writing.\n", argv[1]);
		exit(1);
	}

	//tell the server how to respond - by sending client fifo name
	fputs(clientfifo, fp);
	fclose(fp);

	//open clientfifo for reading and read the quote & print in the screen - improve your life! :-)
	FILE *quotefp = fopen(clientfifo, "r");
	char buffer[MAXLEN] = "";
	fgets(buffer, MAXLEN, quotefp); //read the quote!
	puts(buffer); //display the quote
	fclose(quotefp);

	unlink(clientfifo); //remove the fifo name
}
