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
	int fd = open("simple.out", O_RDONLY);
	//read one char at a time, until you see \0
	int i=0;
	do {
		read(fd, &name[i], 1);
	} while (name[i++]);
	// read(fd, name, strlen(name)+1); 
	read(fd, &age, sizeof(int));
	read(fd, &gpa, sizeof(double));
	close(fd);
	printf("%s %d %lf\n", name, age, gpa);

	//read the data from simple2.out
	FILE *bfp = fopen("simple2.out", "rb");
	//fread(name, 1, strlen(name)+1, bfp);
	i=0;
	do {
		fread(&name[i], 1, 1, bfp);
	} while (name[i++]);
	fread(&age, sizeof(int), 1, bfp);
	fread(&gpa, sizeof(double), 1, bfp);
	fclose(bfp);
	printf("%s %d %lf\n", name, age, gpa);
}

	//while ((n = read(STDIN_FILENO, buf, limit)) > 0)
	//		read(STDOUT_FILENO, buf, n);
