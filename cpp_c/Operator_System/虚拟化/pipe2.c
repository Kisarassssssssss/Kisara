#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    int pipefd[2];
    pid_t pid1,pid2;
    if(pipe(pipefd)==-1)
    {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
    pid1=fork();
    if(pid1<0){
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    if(pid1==0)
    {
        dup2(pipefd[1],STDOUT_FILENO);//子进程1重定向写道管道
        close(pipefd[0]);
        close(pipefd[1]);
        execlp("ls","ls","-l",NULL);
        perror("execlp ls falied");
        exit(EXIT_FAILURE);
    }
    pid2=fork();
    if(pid2<0){
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    if(pid2==0)
    {
        dup2(pipefd[0],STDIN_FILENO);//重定向输入
        close(pipefd[0]);
        close(pipefd[1]);//关闭外部wait才不会阻塞
        execlp("grep","grep",".c",NULL);
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    /*
        exex规范：程序名，还是程序名(规范),参数，NULL；
        ls列出所有文件， -l表示详细参数
        grep 抓取包含参数的文件名并输出
    */
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
    printf("finished");
    return 0;    
}