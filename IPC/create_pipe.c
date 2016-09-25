#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int
main(void)
{
	int fd[2]; // 管道的文件描述符数组
	char str[256];
	extern int errno;

	if( pipe(fd) < 0){ // 创建管道
		printf("create the pipe failed\n");
		exit(-1);
	}

#if 0
	// fd[0]:读出端的文件描述符
	// fd[1]:写入端的文件描述符
	write(fd[1],"create the pipe successfully!\n",31);

	read(fd[0],str,sizeof(str));//256

	printf("sizeof(str) is %d\n",sizeof(str));
	printf("%s",str);
	
	printf("pipe file descriptors are %d,%d\n",fd[0],fd[1]);

	close(fd[0]);// 关闭管道的读出端文件描述符
	close(fd[1]);// 关闭管道的写入端文件描述符

	#endif

#if 0
	//向 管道读端 写入数据
	errno = 0;
//errno is 9, error string is Bad file descriptor
	write(fd[0],"create the pipe successfully!\n",31);
	printf("errno is %d, error string is %s\n",errno,strerror(errno));

	
	errno = 0;//没有读到数据。一直阻塞在read调用上。
	read(fd[0],str,sizeof(str));//256
	printf("errno is %d, error string is %s\n",errno,strerror(errno));


	printf("sizeof(str) is %d\n",sizeof(str));
	printf("%s",str);
	
	printf("pipe file descriptors are %d,%d\n",fd[0],fd[1]);

	close(fd[0]);// 关闭管道的读出端文件描述符
	close(fd[1]);// 关闭管道的写入端文件描述符

#endif

#if 0
	
	errno = 0;
	write(fd[1],"create the pipe successfully!\n",31);
	printf("errno is %d, error string is %s\n",errno,strerror(errno));

	//试图从  管道写端读取数据
	errno = 0;
	read(fd[1],str,sizeof(str));//256
//errno is 9, error string is Bad file descriptor
	printf("errno is %d, error string is %s\n",errno,strerror(errno));


	printf("sizeof(str) is %d\n",sizeof(str));
	printf("%s",str);
	
	printf("pipe file descriptors are %d,%d\n",fd[0],fd[1]);

	close(fd[0]);// 关闭管道的读出端文件描述符
	close(fd[1]);// 关闭管道的写入端文件描述符
#endif

#if 1
	close(fd[0]);// 关闭管道的读出端文件描述符
	printf("xxxx\n");
	errno = 0;
	int ret = 0;

/*

当对一个读端已经关闭的管道进行写操作时，会产生SIGPIPE，说明管道读端已经关闭，并且write操作返回-1,errno的值设置为EPIPE，对于SIGPIPE信号可以进行捕捉处理。（？？？？？）

如果写入进程不能捕捉或者干脆忽略SIGPIPE信号，则写入进程会中断。
*/

	ret = write(fd[1],"create the pipe successfully!\n",31);
	printf("ret is %d\n",ret);// 后面没有执行。
	printf("errno is %d, error string is %s\n",errno,strerror(errno));

	
	errno = 0;
	read(fd[0],str,sizeof(str));//256
	printf("errno is %d, error string is %s\n",errno,strerror(errno));


	printf("sizeof(str) is %d\n",sizeof(str));
	printf("%s",str);
	
	printf("pipe file descriptors are %d,%d\n",fd[0],fd[1]);

	close(fd[0]);// 关闭管道的读出端文件描述符
	close(fd[1]);// 关闭管道的写入端文件描述符

#endif

	return 0;
}

/*
管道的2端是固定了任务的；

即：管道的读出端只能用于读取数据；管道的写入端则只能用于写入数据；

如果试图从  管道写端读取数据。或者向 管道读端写入数据都将  导致错误发生。



一般文件的I/O函数都可以用于管道。比如close,read,write等等。


*/

/*
管道的读取规则是：
如果管道的写端不存在，则认为已经读到了数据 的末尾。
读函数返回的读出字节数为0.

当管道的写端存在时，如果请求的字节数目大于PIPE_BUF,

则返回管道中现有的数据字节数。

如果请求的字节数目不大于PIPE_BUF，则返回管道中现有
数据字节数（此时，管道中的数据量  小于 请求的数据量）；
或者返回 请求的字节数（此时，管道中数据量不小于请求的数据量。）


PIPE_BUF在include/linux/limits.h中定义。不同的内核版本可能会有所不同。

POSIX.1要求PIPE_BUF至少为512字节。


另外，在进行读写管道时，对一个管道进行读操作后，read函数返回0，有2种含义：
1）管道中没有数据并且写入端关毕（也就是写入端不存在）。

2）管道中没有数据写入端依然存活。
这2种情况要根据需要分别处理。



管道的写入规则是：向管道中写入数据时，管道缓冲区一旦有空闲区域，写进程就好
立即试图向管道中写入数据。

如果读进程没有读取  管道缓冲区中的数据，那么写操作将一直阻塞。



只有在管道的读端存在时，向管道中写入数据才有意义。否则，向

管道中写入数据的进程将收到内核传来的SIGPIPE信号，应用程序可以处理该信号。
也可以忽略（默认动作则是应用程序终止。） 我明白了。


单独一个进程操作管道是没有任何意义的。管道的应用一般


体现在父子进程  或者 兄弟进程的通信。



*/


