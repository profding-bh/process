#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>

//没有发现PIPE_BUF 的定义

#define  PIPE_BUF  4096
#define BUFSIZE PIPE_BUF


void err_quit(char* msg)
{
	printf(msg);
	exit(1);
}


int
main(void)
{
	int fd[2]; // 管道的文件描述符数组
	char buf[BUFSIZE]="hello my child!\n";
	char str[BUFSIZE];
	pid_t pid;
	int len;
	extern int errno;

	if( pipe(fd) < 0){ // 创建管道
		err_quit("pipe failed\n");
	}

	
/*

parent fd[0] is 3 0x7ffde39ccb20 fd[1] is 4 0x7ffde39ccb24
child fd[0] is 3 0x7ffde39ccb20 fd[1] is 4 0x7ffde39ccb24

Q: 为什么地址会一样？？按道理，fork之后，父子进程没有共享数据段啊？？？？

A：不同地址空间中，一样的地址。copy



*/

// 实现数据从父进程流向子进程。

	if( (pid=fork()) < 0 ){
		err_quit("fork failed\n");
	} else if(pid > 0){
		printf("parent fd[0] is %d %p fd[1] is %d %p\n",fd[0],&fd[0],fd[1],&fd[1]);
		close(fd[0]); // 父进程关闭 管道的读出端
		write(fd[1],buf,strlen(buf));//父进程向管道中写入数据
		exit(0);
	}else{
		// child
		printf("child fd[0] is %d %p fd[1] is %d %p\n",fd[0],&fd[0],fd[1],&fd[1]);
		close(fd[1]); // 子进程关闭 管道的写入端
		len = read(fd[0],str,BUFSIZE);
		if(len < 0){
			err_quit("process  failed when read a pipe\n");
		}else{
			write(STDOUT_FILENO,str,len);
//  STDOUT_FILENO 1
//  STDIN_FILENO 0
//  STDERR_FILENO 2
		}
		exit(0);
	}
	return 0;
}

/*
单独一个进程操作管道是没有任何意义的。管道的应用一般


体现在父子进程  或者 兄弟进程的通信。

*/


