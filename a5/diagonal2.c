#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define LINESIZE 16
int makespace(int fd, int count){
	//create a file so that 16 rows of empty will appear with od -c command
	char space = ' ';
	for(int line=0; line<LINESIZE * count; line++)
		for(int column=0; column<LINESIZE; column++)
			write(fd, &space, 1);

}

int oddPattern(char word[], int fd, int offset){
	int n = strlen(word);
	for(int i=0; i<n; i++) {
		lseek(fd, offset + (LINESIZE+1)*i, SEEK_SET);
		write(fd, &word[i], 1);
	}
}

int evenPattern(char word[], int fd, int offset){
	int n = strlen(word);
	for(int i=0; i<n; i++) {
		lseek(fd,offset + (LINESIZE-1)*(i + 1), SEEK_SET);
		write(fd, &word[i], 1);
	}
}
//use one command line argument
int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: diagonal2 <textstring>\n");
		return -1;
	}
	int length = argc;
	int fd = open("diagonal2.out", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	makespace(fd, length - 1);
	for(int i = 1; i < length; i++){
		//evenPattern(argv[i], fd);
		int offset = 256 * (i - 1);
		if(i % 2  == 1){
			oddPattern(argv[i], fd, offset);
		}
		else{
			evenPattern(argv[i], fd, offset);
		}
	}
	//create a file so that 16 rows of empty will appear with od -c command
	close(fd);
	puts("diagonal2.out has been created. Use od -c diagonal2.out to see the contents.");
}
