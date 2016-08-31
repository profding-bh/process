#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int
main(void)
{
    int count = 1;
    pid_t  pid;

    printf("before create son ,parent count is %d\n",count);

    pid = vfork();// 这里是vfork

    if(pid < 0)
    {
         printf("error in fork\n");
         exit (EXIT_FAILURE);
    }else if(0 == pid){
            int i;
            for(i=0;i<100;++i)
            {
                printf("child i is %d\n",i);
                if(70 == i)
                {
                    exit(1);// will awake parent process
                }
            }
            printf("child process,the count is %d,my pid is %d\n",++count,getpid());
			exit(1);
    }else{
            printf("parent process,the count is %d,my pid is %d,child is %d\n",count,getpid(),pid);
    }
    return EXIT_SUCCESS;
}


