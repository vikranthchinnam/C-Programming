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

	//store all of them in text file 
	FILE *fp = fopen("simple.txt", "w");
	fprintf(fp, "%s %d %lf\n", name, age, gpa);
	fclose(fp);

	//store all of them in binary file using system calls
	int fd = open("simple.out", O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP);
	write(fd, name, strlen(name)+1); //store extra char to include \0
	write(fd, &age, sizeof(int));
	write(fd, &gpa, sizeof(double));
	close(fd);

	//store all of them in binary file using C library
	FILE *bfp = fopen("simple2.out", "wb");
	fwrite(name, 1, strlen(name)+1, bfp);
	fwrite(&age, sizeof(int), 1, bfp);
	fwrite(&gpa, sizeof(double), 1, bfp);
	fclose(bfp);
}

	//while ((n = read(STDIN_FILENO, buf, limit)) > 0)
	//		write(STDOUT_FILENO, buf, n);
