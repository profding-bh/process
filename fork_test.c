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
			exit (EXIT_SUCCESS);
    }else{
			sleep(1);// 测试子进程调用exit(0)之后，是否会影响父进程。
            printf("parent process,the count is %d,my pid is %d\n",++count,getpid());
    }
    return EXIT_SUCCESS;
}

// 发现子进程调用exit()之后，并不会干掉 父进程。说明，父，子进程创建好之后，就互不影响了。
