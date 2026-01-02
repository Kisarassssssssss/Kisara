#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
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
        printf("hello,i am child(pid:%d)\n",(int)getpid());
    }else {
        int wc=wait(NULL);
        /*
            逻辑上： 父进程在等子进程结束。
            物理上： 父进程的 PCB 被移出了 CPU 的调度循环。
            性能上： 这种等待是 “被动等待”（不消耗 CPU 资源），而不是像 while(1) 那样消耗 CPU 的“忙等待”。
        */
        printf("hello,i am parent of%d(wc:%d)(pid:%d)\n",rc,wc,(int)getpid());
    }
    return 0;
}