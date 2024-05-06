#include <stdio.h>
#include <stdlib.h>

#define BUFFSIZE 1000000
char buf[BUFFSIZE];

int main(int argc, char *argv[]) {
	int limit = atoi(argv[1]);
	int n;
	while ((n = fread(buf, 1, limit, stdin)) > 0)
		fwrite(buf, 1, n, stdout);
}
