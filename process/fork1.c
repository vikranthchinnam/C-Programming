#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Before fork...\n");
	fork();
	printf("Hello from %d! My parent is %d.\n", getpid(), getppid());
	//printf("Good place!\n");
}
