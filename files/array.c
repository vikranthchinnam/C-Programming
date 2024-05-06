#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(){
	int length;
	printf("Please enter an integer N : ");
	scanf("%d", &length);
	int *array = (int*) malloc(length * sizeof(int));
	for(int i = 0; i < length; i++){
		scanf("%d", &array[i]);
	}

	
	//store all of them in text file 
	FILE *fp = fopen("array.txt", "w");
	for(int i = 0; i < length; i++){
		fprintf(fp, "%d ", array[i]);
	}
	fputc('\n', fp);
	fclose(fp);
	


	//store all of them in binary file using C library
	FILE *bfp = fopen("array.out", "wb");
//	for(int i = 0;  i < length; i++){
//		fwrite(array[i], sizeof(int), 1, bfp);
//	}
	fwrite(&length, sizeof(int), 1, bfp);
	fwrite(array, sizeof(int), length, bfp);
	
	fclose(bfp);
}
