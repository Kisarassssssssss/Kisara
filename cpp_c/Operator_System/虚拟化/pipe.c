#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int p[2];//管道需要两个整数的数组，p[0]读取，p[1]写入
    if(pipe(p)<0){
        perror("pipe failed");
        exit(1);
    }//创建单项流动的数据管道，内核会分配两个可用的文件描述符存入 p 数组中。现在，往 p[1] 写入的任何数据，都可以从 p[0] 读取出来。
    __pid_t rc=fork();
    if(rc<0)
    {
        perror("fork failed");
        exit(1);
    }else if(rc==0)
    {
        printf("hello\n");//子进程开始
        close(p[1]);//关闭写入端，读取端p[0]会读到EOF
    }else{
        char buf;
        read(p[0],&buf,1);//子进程没有数据，管道为空且端口打开，一直阻塞
        //只有端口关闭才返回

        printf("goodbye\n");
        close(p[0]);
    }
    return 0;

    /*
    IPC(进程间通信)：Pipe：把一个进程的输出，直接变成另一个进程的输入
    单向性：一头读，一头写；
    同步阻塞：没数据且通畅：阻塞；
    */
} 