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
// fork之后，引入的问题：父子进程如何共享数据？？？？
// 
// vfork，挂起父进程，子进程先运行。
// 而vfork则不需要完全复制父进程的数据段，在子进程没有调用exec或exit之前，子进程与父进程共享数据段。（？？）
// fork不对父子进程的执行次序进行任何限制。
// 由vfork创造出来的子进程还会导致父进程挂起，除非子进程执行了exit 或者 execve才会唤起父进程。

    if(pc < 0)
    {
         printf("error in fork\n");
         exit (EXIT_FAILURE);
    }else if(0 == pc){
            printf("child process,my pid is %d\n",getpid());
			sleep(4);
    }else{

			// pr = waitpid(-1,NULL,0); // 还是挂起啊～～～
			// pr = waitpid(-1,NULL,WNOHANG); // 直接返回
			pr = waitpid(-1,NULL,WUNTRACED); // 还是挂起啊～～～
            printf("parent process,i catched a child process with pid of %d\n",pr);
    }


    return EXIT_SUCCESS;	
}





