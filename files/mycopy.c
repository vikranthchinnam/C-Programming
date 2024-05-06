#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 1000000
char buf[BUFFSIZE];

int main(int argc, char *argv[]) {
	int limit = atoi(argv[1]);
	int n;
	while ((n = read(STDIN_FILENO, buf, limit)) > 0)
		write(STDOUT_FILENO, buf, n);
}
