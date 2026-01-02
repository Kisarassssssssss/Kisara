#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
    printf("hello world (pid:%d)\n",(int) getpid());
    int rc=fork();
    if(rc<0)
    {
        fprintf(stderr,"fork failed\n");
        exit(1);
    }else if(rc==0)
    {
        printf("hello,i am child(pid:%d)",(int)getpid());
    }else {
        printf("hello,i am parent of%d(pid:%d)\n",rc,(int)getpid());
    }
    /*
        。进程调用了 fork()系统调用，这是操作系统提供的创建新进程的方法。
        新创建的进程几乎与调用进程完全一样，对操作系统来说，这谁看起来有两个完
        全一样的 p1 程序谁运行，并都从 fork()系统调用中返回。新创建的进程称为子进程（child），
        原来的进程称为父进程（parent）。子进程不会会从 main()函数开始执行（因此 hello world 信
        息只输出了一次），而是直接从 fork()系统调用返回，就好像是它自己调用了 fork()。
    */
    return 0;
}