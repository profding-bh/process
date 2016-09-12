#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include<sys/wait.h>


int
main(void)
{
	int status;
    pid_t  pc,pr;
	extern int errno;

// get
	printf("getuid %d\n",getuid());
	printf("getgid %d\n",getgid());
	printf("geteuid %d\n",geteuid());
	printf("geteguid %d\n",getegid());

	errno = 0;
//
	printf("setuid %d\n",setuid(100));
	printf("errno  is  %d  string is %s\n",errno,strerror(errno));

	errno = 0;
//
	printf("setgid %d\n",setgid(30));
	printf("errno  is  %d  string is %s\n",errno,strerror(errno));
    pc = fork();// 这里是fork


	

	
    if(pc < 0)
    {
         printf("error in fork\n");
         exit (EXIT_FAILURE);
    }else if(0 == pc){
            printf("child process,my pid is %d\n",getpid());
	        
			printf("child getuid %d\n",getuid());
			printf("child getgid %d\n",getgid());
			printf("child geteuid %d\n",geteuid());
			printf("child geteguid %d\n",getegid());
	
			sleep(3);
/*
2种自杀方式：
exit or return.

*/
			//exit(0);
			return 9;
    } else{ 
	 
		
	  // 父进程代码
			// pc存了子进程的id
			pr = wait(&status); 
			if(WIFEXITED(status))
			{
				// 如果WIFEXITED返回非0值
				printf(" child process %d exited normally!\n",pr);
				printf("the return code is %d.\n",WEXITSTATUS(status));
			} else{
			   // 如果WIFEXITED返回0值
              printf(" child process %d exited abnormally!\n",pr);
 			 }
	}

/*

当WIFEXITED返回非0值时，可以使用WEXITSTATUS（status）这个宏来提取子进程的返回值。
比如如果 子进程调用exit(0)退出，WEXITSTATUS（status）就会返回0；
如果 子进程调用exit(7)退出，WEXITSTATUS（status）就会返回7；


注意：
如果 子进程 不是正常退出的，WIFEXITED返回0,这个值没有意义。

*/
    return EXIT_SUCCESS;	
}





