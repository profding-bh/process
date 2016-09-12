#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>


int
main(void)
{

    pid_t  pc,pr;
    pc = fork();// 这里是fork

    if(pc < 0)
    {
         printf("error in fork\n");
         exit (EXIT_FAILURE);
    }else if(0 == pc){
            printf("child process,my pid is %d\n",getpid());
			sleep(5);
    }else{
			pr = wait(NULL); // 等待子进程，父进程挂起
            printf("parent process,i catched a child process with pid of %d\n",pr);
    }
    return EXIT_SUCCESS;
	
}


