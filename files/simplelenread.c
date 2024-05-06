#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char name[100];
	int age;
	double gpa;

	//read the data from simple.out
	int fd = open("simplelen.out", O_RDONLY);
	//read one char at a time, until you see \0
	int n = 1;
	read(fd, &n, sizeof(int));
	read(fd, name, n);
	// read(fd, name, strlen(name)+1); 
	read(fd, &age, sizeof(int));
	read(fd, &gpa, sizeof(double));
	close(fd);
	printf("%s %d %lf\n", name, age, gpa);

}

	//while ((n = read(STDIN_FILENO, buf, limit)) > 0)
	//		read(STDOUT_FILENO, buf, n);
