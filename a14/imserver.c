#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>  
#include <inttypes.h>  
#include <pthread.h>
#include <errno.h>   
#include <fcntl.h>     
#define MAXLEN 1000
int users[MAXLEN];
char dict[100000][MAXLEN];
int numUsers = 0;
int counter = 0;
int userActive[MAXLEN];
void pexit(char *errmsg) {
	fprintf(stderr, "%s\n", errmsg);
	exit(1);
}
void *child( void *ptr )
{
	int idx = (int *) ptr;
	int connfd = users[idx];
	srand(getpid() + idx + connfd);	
	char userName[20];
	sprintf(userName, "user%d", numUsers);
	char buffer[1024];
	int n = 0;
	n = sprintf(buffer, "Welcome! \n\n");
	write(connfd,buffer, n);
	char command[5];
	char list[5] = "list";
	char send[5] = "send\0";
	char broadcast[10] = "broadcast\0";
	char random[7] = "random\0";
	char closeString[6] = "close\0";
	int misses = 0;
	char curr;
	char message[MAXLEN];
	while(n = read(connfd, message, MAXLEN)){
		if(buffer[0] == '\n'){
			continue;
		}
		char *token = strtok(message, " ");
		int j = 0;
		while(*token != '\0'){
			if(*token == '\n'){
				token++;
				continue;
			}
			buffer[j] = *token;
			j++;
			token++;
		}
		buffer[j] = '\0';
		if(strcmp(buffer, list) == 0){
			for(int i = 1; i < numUsers + 1; i++){
				if(userActive[i - 1] == 0){
					continue;
				}
				n = sprintf(buffer, "user%d ", i);
				write(connfd, buffer, n);
			}
			n = sprintf(buffer, "\n");
			write(connfd, buffer, n);
		}
		else if(strcmp(buffer, send) == 0){
			strncpy(message, message + 9, MAXLEN);
			
			char *usernumber = strtok(message, " ");
			int userIndex = atoi(usernumber);
			if(--userIndex < 0 || userActive[userIndex] == 0){
				n = sprintf(buffer, "Sorry, user%d is not on the server.\n", userIndex + 1);
				write(connfd, buffer, n);
			}
			else{
				int senderfd = users[userIndex];
				strncpy(message, message + strlen(usernumber) + 1, MAXLEN);
				n = sprintf(buffer, "%s says %s\n", userName, message);
				write(senderfd, buffer, n);
			
			}
		}
		else if(strcmp(buffer, broadcast) == 0){
			strncpy(message, message + 10, MAXLEN);
			for(int i = 0; i < numUsers; i++){
				if(userActive[i] == 0){
					continue;	
				}
				n = sprintf(buffer, "%s\n", message);
				write(users[i], buffer, n);
			}
		}
		else if(strcmp(buffer, random) == 0){
			strncpy(message, message + 7, MAXLEN);
			int senderIndex = rand() % counter;
			while(userActive[senderIndex] == 0){
				senderIndex++;
			}
			int senderfd = users[senderIndex];
			n = sprintf(buffer, "%s randomly says %s\n", userName, message);
			write(senderfd, buffer, n);
		}
		else if(strcmp(buffer, closeString) == 0){
			userActive[idx]	= 0;
			close(connfd);
			counter--;
			break;
		}

		memset(buffer, '\0', sizeof(buffer));
		memset(message, '\0', sizeof(message));
	}
}
int main(){
	char line[MAXLEN];
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
	do {
 		port++;
		serv_addr.sin_port = htons(port);
	} while (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0);
	
	printf("bind() succeeds for port #%d\n", port);
	if (listen(listenfd, 10) < 0)
		pexit("listen() error.");
		
	while(1){
		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
		users[numUsers] = connfd;
		userActive[numUsers] = 1;
		numUsers++;
		counter++;
		pthread_t thread1;
		
		char userName[20];
		sprintf(userName, "user%d", numUsers);
		printf("%s joined ! \n\n\n", userName);
		pthread_create(&thread1, NULL, child, (void *) numUsers - 1);

	}

}
