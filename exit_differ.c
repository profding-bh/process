#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int
main(void)
{
  
    pid_t  pid;

    pid = fork();

    if(pid ==  -1)
    {
         printf("error in fork\n");
         exit(EXIT_FAILURE);
    }else if(0 == pid){
		
/*

printf函数在遇到'\n'，才从缓冲区中读取数据。

*/
            printf("child process,output begin \n");
			printf("child process,content in buffer");// 没有换行符
			exit(EXIT_SUCCESS);
    }else{
			printf("parent process,output begin \n");
			printf("parent process,content in buffer");// 没有换行符
			_exit(EXIT_SUCCESS); // _exit
    }
    return EXIT_SUCCESS;
}

