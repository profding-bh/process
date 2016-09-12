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
			sleep(4);
			exit(0);
    }

	 printf("---- pid is %d\n",getpid());
// 父进程代码
	do{
			// pc存了子进程的id
			pr = waitpid(pc,NULL,WNOHANG); // 
			if(0 == pr)
			{
				// 没有收集到子进程
				printf("No child exited\n");
				sleep(1);
			}
           // printf("parent process,i catched a child process with pid of %d\n",pc);
    }while(0 == pr); // 没有收集到子进程，就继续尝试。

/*

 父进程，和 子进程 分别睡眠4s 和 1s,代表
它们分别做了4s和1s的工作。

父子进程都有工作要做，父进程利用简短间歇查看子进程是否退出。如果退出，

就收集他。


*/
	if(pr == pc)
	 	printf("successfully get child %d\n",pr);
	else
		printf("error\n");

    return EXIT_SUCCESS;	
}





