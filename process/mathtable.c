#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	int i;
	for(i=1; i<100; i++)
		if (!fork()) {
			break;
		}
	printf("%3d * %2d = %5d\n", n, i, n*i);
}
