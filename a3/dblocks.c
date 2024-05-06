#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define SIBLOCKS 2048L
#define DIBLOCKS (2048L*2048L)
#define TIBLOCKS (2048L*2048L*2048L)

long computeOverheadBlocks(long diskblocks) {
	//CODE HERE!
	long result = diskblocks - 12;
	long total = 0;
	if(result <= 0){
		return 0;
	}
	long baseOverheadBlocks = result / 2048;
	if (result  % 2048 != 0){
		baseOverheadBlocks++;
	}
	total++;
	baseOverheadBlocks--;
	if(baseOverheadBlocks <= 0){
		return total;
	}	
	if(baseOverheadBlocks <= 2048){
		total = total + baseOverheadBlocks + 1;
		return total;
	}
	total = total + 2048 + 1;
	baseOverheadBlocks = baseOverheadBlocks - 2048;


	long secondLevelBlocks = baseOverheadBlocks / 2048;
	if(baseOverheadBlocks % 2048 != 0)
		secondLevelBlocks++;	
	if(secondLevelBlocks > 2048){
		return -1;
	}

	return total + secondLevelBlocks + baseOverheadBlocks  + 1;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: diskblocks <file size in KBs>\n");
		return -1;
	}
	long filesize = atol(argv[1]);
	long diskblocks = filesize / 8;
	if (filesize % 8) 
		diskblocks++;

	printf("%ld %ld\n", diskblocks, computeOverheadBlocks(diskblocks));
}
