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
	char buf[BUFSIZE]="hello my sibling!\n";
	char str[BUFSIZE];
	pid_t pid;
	int len;
	extern int errno;

	if( pipe(fd) < 0){ // 创建管道
		err_quit("pipe failed\n");
	}

/*
	close(fd[0]); 
	close(fd[1]); 
*/

	printf("parent fd[0] is %d %p fd[1] is %d %p\n",fd[0],&fd[0],fd[1],&fd[1]);

	if( (pid=fork()) < 0 ){ //创建子进程1 
		err_quit("fork 1 failed\n");
	} else if(pid == 0){
		// child  1
		printf("child 1 fd[0] is %d %p fd[1] is %d %p\n",fd[0],&fd[0],fd[1],&fd[1]);
		close(fd[0]); // 子进程1 关闭 管道的读出端,关闭不使用的文件描述符
		write(fd[1],buf,strlen(buf));// 子进程1 向管道中写入数据
		exit(0);
	}

// 子进程1 --发送数据 给  子进程2


/*
	程序中，父进程在创建第1个子进程时，并没有关闭管道2端。

	而是在创建第2个进程时，才关闭管道；这是为了在创建第2个进程时，

子进程可以继承活的管道，而不是一个2端已经关闭的管道。


*/
	// 父进程
	if( (pid=fork()) < 0 ){ //创建子进程2 
		err_quit("fork 2 failed\n");
	} else if(pid > 0){
		// 父进程
		close(fd[0]); // 父进程 关闭 管道的读出端
		close(fd[1]); // 父进程 关闭 管道的写入端 
		exit(0);
	}else { // 子进程2 
		printf("child 2 fd[0] is %d %p fd[1] is %d %p\n",fd[0],&fd[0],fd[1],&fd[1]);
		close(fd[1]);// 关闭不使用的文件描述符
		len = read(fd[0],str,BUFSIZE);// 读取
		write(STDOUT_FILENO,str,len);// 输出
		exit(0);
	}
	
	return 0;
}

/*
管道在兄弟进程间应用时，应该先在父进程中，建立管道。然后调用fork函数创建
2个子进程，在兄弟进程之间维护管道的数据流向。


这里的问题是，维护管道的顺序，当父进程 创建了管道，只有子进程已经继承了
管道之后，父进程才可以关闭管道；

如果在fork之前，已经关闭管道，子进程将不能继承任何可以使用的管道。


*/


