#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void noThreads() {
	fprintf(stderr, "Failed to create Thread.\n");
	exit(1);
}

//fib(0): 1
//fib(1): 1
//fib(n) = fib(n-1) + fib(n-2)
void *fib( void *ptr )
{
	int n = (int) ptr;
	if (n < 2)
		return (void *) 1;

	//CODE for fib(n) n >= 2
	//create 2 threads to compute fib(n-1) and fib(n-2)
     pthread_t thread1, thread2;
     if (pthread_create(&thread1, NULL, fib, (void *) n-1))
     	noThreads();

     if (pthread_create(&thread2, NULL, fib, (void *) n-2))
     	noThreads();
	
	//add return values and return the total
	 void *ptr1, *ptr2;
     pthread_join(thread1, &ptr1);
     pthread_join(thread2, &ptr2);
	
	 int sum = (int) ptr1 + (int) ptr2;
	 return (void *) sum;
}

int main(int argc, char *argv[])
{
	 int target = atoi(argv[1]);
     pthread_t thread1;
     if (pthread_create(&thread1, NULL, fib, (void *) target))
     	noThreads();

	 void *ptr;
     pthread_join(thread1, &ptr);
	 printf("fib(%d) = %d\n", target, (int) ptr);

     exit(0);
}

