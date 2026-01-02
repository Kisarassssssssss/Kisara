#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/*
    exec():
    PID（进程 ID）不变：在操作系统看来，这还是原来的那个进程。
    内存被清空：原本进程的代码段、数据段、堆和栈全部被扔掉。
    重新加载：操作系统把一个新程序（比如 ls 或 python）加载到这个进程的内存空间里。
    从头开始：新程序从它的 main() 函数开始重新执行。
    一句话总结：身体（PID）还是原来的，但灵魂（代码和数据）彻底换人了。
    如果成功执行，不能返回；  
*/
int main() {
    printf("我是父进程 (PID: %d)，我准备分身了...\n", getpid());

    pid_t pid = fork();//创建子进程

    if (pid < 0) {
        perror("fork 失败");
        exit(1);
    } 
    else if (pid == 0) {
        // --- 这里是子进程 ---
        printf("我是子进程 (PID: %d)，我即将变身为 'ls' 命令！\n", getpid());

        /* 
         * 调用 execlp 函数:
         * 参数1: 要执行的程序名
         * 参数2: 给程序的第一个参数（通常是程序名本身）
         * 参数3: 传递给 ls 的参数 "-l"
         * 参数4: 必须以 NULL 结尾，告诉系统参数结束了
         */
        execlp("ls", "ls", "-l", NULL);

        // 【非常重要】：如果 execlp 执行成功，下面这行代码永远不会被执行！
        // 因为子进程的代码已经被 ls 的代码替换掉了。
        printf("如果你看到这行，说明 exec 失败了！\n");
    } 
    else {
        // --- 这里是父进程 ---
        int wc = wait(NULL); // 等待子进程变身执行完毕
        printf("我是父进程，刚才那个变身的子进程 (PID: %d) 已经干完活退出了。\n", wc);
    }

    return 0;
}