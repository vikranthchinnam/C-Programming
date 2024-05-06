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

	//get name, age, and gpa
	scanf("%s%d%lf", name, &age, &gpa);
	printf("%s %d %lf\n", name, age, gpa);

	int fd = open("simplelen.out", O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP);
	//store the string length first, before the string content
	int n = strlen(name)+1; // Include NULL character too
	write(fd, &n, sizeof(int));
	write(fd, name, n); 
	write(fd, &age, sizeof(int));
	write(fd, &gpa, sizeof(double));
	close(fd);

}
