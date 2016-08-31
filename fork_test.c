#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int
main(void)
{
    int count = 0;
    pid_t  pid;

    pid = fork();

    if(pid < 0)
    {
         printf("error in fork\n");
         exit (EXIT_FAILURE);
    }else if(0 == pid){
            printf("child process,the count is %d,my pid is %d\n",count,getpid());
    }else{
            printf("parent process,the count is %d,my pid is %d\n",++count,getpid());
    }
    return EXIT_SUCCESS;
}


