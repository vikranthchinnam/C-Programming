#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	//A null terminated array of character pointers 
	char *args[]={"child",NULL}; 
	execvp(args[0],args);
      
    //All statements are ignored after execvp() 
    printf("I hope you won't see me!\n");
      
    return 0;
}
