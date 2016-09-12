#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>


int
main(void)
{
  	pid_t pid;
	printf("no child process to wait!\n");
	
	extern int errno;
	errno = 0;
	pid = wait(NULL);

/*

如果成功，wait会返回被收集的子进程的进程ID;如果调用进程没有子进程，调用
就会失败，此时wait返回-1,同时errno被设置为ECHILD:(no child processes)

*/
	printf("pid is %d ,errno is %d string is %s\n",pid,errno,strerror(errno));
	
	return EXIT_SUCCESS;
}


