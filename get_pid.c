#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int 
main(void)
{
	printf("The current process ID is %d\n",getpid());
	return EXIT_SUCCESS;
}
