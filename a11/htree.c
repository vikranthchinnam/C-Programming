#include <stdint.h>  
#include <inttypes.h>  
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <errno.h>   
#include <fcntl.h>     
#include <unistd.h>    
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
// Print out the usage of the program and exit.
void usage(char*);
uint32_t jenkins_one_at_a_time_hash(const uint8_t* , uint64_t );
char *buffer;
int numThreads;
uint64_t blockSize;
void *child( void *ptr )
{
	uint32_t n = (uint32_t) ptr;
	pthread_t thread1, thread2;
	bool child1 = false, child2 = false;
	if (2*n+1 < numThreads) {
     		pthread_create(&thread1, NULL, child, (void *) (2*n+1));
		child1 = true;
	 	if (2*n+2 < numThreads) {
     			pthread_create(&thread2, NULL, child, (void *) (2*n+2));
			child2 = true;
		}
	}

	char *ptr1 = NULL, *ptr2 = NULL;
	
	uint32_t hash = jenkins_one_at_a_time_hash(buffer + n*blockSize, blockSize);
	if (child1){
		pthread_join(thread1, &ptr1);

	}
	else{
		uint32_t total = hash;
		return (void *) total;
	}
	if (child2){
		pthread_join(thread2, &ptr2);
		char combineBuffer[100];
		sprintf(combineBuffer, "%u%u%u", hash, (uint32_t) ptr1, (uint32_t) ptr2);
		hash = jenkins_one_at_a_time_hash(combineBuffer, strlen(combineBuffer));
	}
	else{
		
		char combineBuffer[100];
		sprintf(combineBuffer, "%u%u", hash, (uint32_t) ptr1);
		hash = jenkins_one_at_a_time_hash(combineBuffer, strlen(combineBuffer));
	}
	
//	uint32_t total = 1 + (uint32_t) ptr1 + (uint32_t) ptr2;

	//printf("Thread %d total %d\n", n, total);
	uint32_t total = (uint32_t) hash;
	return (void *) total;
}
int main(int argc, char *argv[]) 
{
  int32_t fd;

  // input checking 
  if (argc != 3)
    usage(argv[0]);


  // open input file
  fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("open failed");
    exit(EXIT_FAILURE);
  }

  numThreads = atoi(argv[2]);
  // use fstat to get file size
  struct stat fileInfo;
  if (fstat(fd, &fileInfo)) {
		perror("file not found.");
		exit(EXIT_FAILURE);
	}
  uint64_t fileSize = fileInfo.st_size;
  blockSize = fileSize / numThreads;
  buffer = (char *) malloc (fileSize);
  if (buffer == NULL) {
		perror("Memory allocation failure.");
		exit(EXIT_FAILURE);
  }
  uint64_t nread = 0;
  ssize_t n = 0;
  //as long as there is more data to read, keep reading! We may need to use multiple read() to read huge files.
  while ((nread < fileSize) && ((n = read(fd, &buffer[nread], fileSize-nread)) > 0)) {
  	nread += n;
	//n = read(fd, &buffer[nread], fileSize-nread);
  }
  	
  if (n < 0) {
		perror("File read error.");
		exit(EXIT_FAILURE);
  	}

  clock_t start = clock();

  // calculate hash value of the whole input file as one big block!
  //uint32_t hash = jenkins_one_at_a_time_hash(buffer, fileSize/2);
   
  pthread_t thread1;
  uint32_t threadNumber = 0;
  pthread_create(&thread1, NULL, child, (void *) threadNumber);
  void *ptr;
  pthread_join(thread1, &ptr); 
  clock_t end = clock();
  uint32_t hash = (uint32_t) ptr;
  printf("number of threads: %d\n", numThreads);
  printf("number of blocks: %u\n", blockSize/4096);
  printf("hash value = %u \n", hash);
  printf("time taken = %f \n", (end - start) * 1.0 / CLOCKS_PER_SEC);
  close(fd);
  return EXIT_SUCCESS;
}


uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, uint64_t length) 
{
  uint64_t i = 0;
  uint32_t hash = 0;

  while (i != length) {
    hash += key[i++];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}


void usage(char* s) 
{
  fprintf(stderr, "Usage: %s filename num_threads\n", s);
  exit(EXIT_FAILURE);
}
