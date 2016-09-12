#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int
main(void)
{
  
	printf("this process will exit!\n");
	exit (EXIT_SUCCESS);
	printf("never execute!\n");   
}


