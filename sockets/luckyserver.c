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

void pexit(char *errmsg) {
	fprintf(stderr, "%s\n", errmsg);
	exit(1);
}

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];
    time_t ticks; 

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		pexit("socket() error.");
		
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int port = 4999;
	do {
		port++;
    	serv_addr.sin_port = htons(port); 
    } while (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0);
	printf("bind() succeeds for port #%d\n", port);

    if (listen(listenfd, 10) < 0)
		pexit("listen() error.");

	int counter=1;
    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

        ticks = time(NULL);
	if(counter > 10){
		break;
	}
        if(counter == 5){
			
        	snprintf(sendBuff, sizeof(sendBuff), "You Win a Free Ticket You are Client %d: %.24s\r\n", counter, ctime(&ticks));
	}
	else if(counter == 10){
        	snprintf(sendBuff, sizeof(sendBuff), "You Win a Free Ticket You are Client %d: %.24s\r\n", counter, ctime(&ticks));
	}
	else{
			
        	snprintf(sendBuff, sizeof(sendBuff), "You win a lottery ticket that doesn't win anything Client %d: %.24s\r\n", counter, ctime(&ticks));
	}
	write(connfd, sendBuff, strlen(sendBuff)); 
		
		printf("served client %d.\n", counter++);
        close(connfd);
        sleep(1);
     }
}
