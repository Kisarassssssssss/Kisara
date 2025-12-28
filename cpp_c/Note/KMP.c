#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 10001
/*
KMP
*/
int next[MAXSIZE]={0};
void Nextbuild(char *t)
{
    next[0]=0;
    int lens=0;//公共缀长度
    int i=1;//后缀指针。它一直往右走（只增不减），表示当前我们正在计算哪个位置的 next 值。
    int lent=strlen(t);
    while(i<lent)//扫描并创建每一个位置的next下标
    {
        /*
        t[lens]可以代表前缀；
        t[i]表示后缀结尾
        */
        if(t[lens]==t[i])//如果匹配，i处的next++,指针移动，看下一个位置
        {
            lens++;
            next[i]=lens;
            i++;
        }
        else if(lens==0)//第一处就不匹配，直接看下一位
        {
            next[i]=0;
            i++;
        }
        else
        {
            lens=next[lens-1];//当前不匹配，看看在这个已匹配的前缀内部，有没有更短的前缀能接上去和后缀再匹配？next数组本身代表了当前位置最长公共前后缀长度，即可以让前缀跳过的长度，我们不妨直接让前缀回到那个长度，再进行匹配
        }
        /*
        状态 1：尝试最长匹配（失败）
我们试图把前缀往后延伸一位，发现不匹配。
后缀部分（主串位置）：  A B A B A [C] ... (当前 i 指向 C)
                    | | | | |   X
前缀部分（模式串）：    A B A B A [D] ... (假设下一个是 D)
这时候匹配断了。
状态 2：拉动前缀，寻找“更小的公共长度”
你的直觉告诉你要“找一个更小的公共长度”。
这就相当于把下面那行字（前缀）往右拉动，直到它再次和上面那行字（后缀）重合（覆盖）。
那么能保留多少重合部分呢？这就看 next[lens-1]。
A B A B A 的最长公共前后缀是 A B A (长度3)。
于是我们**“拉动”**前缀，让开头的 A B A 去覆盖刚才结尾的 A B A：
code
Text
后缀部分（主串位置）：  A B A B A [C] ... (i 依然指向 C，没动)
                    | | |   ?
前缀部分（模式串      A B A [B] ... (lens 变成了 3)
看！这就是你说的“拉动覆盖”。
现在我们只需要拿前缀的第 4 个字符（B）去和上面的 C 继续比。


匹配时：就像拉拉链，一位一位扣上（lens++, i++）。
不匹配时：拉链卡住了。不要把拉链全部拉开（不要 i 回溯，也不要 lens=0）。
策略：根据 next 表，把前缀那端往右抽动一下（lens = next[lens-1]），找到下一个能**咬合（覆盖）**的位置，继续试。

        */
    }
}
int KmpSearch(char *s,char *t)
{
    int lens=strlen(s);
    int lent=strlen(t);
    Nextbuild(t);
    int i=0,j=0;
    int index=-1;
    while(i<lens)
    {
        /*
        1->匹配成功，移位
        2->第一个就不匹配，主串移位
        3->中间不匹配，把子串回朔到合适位置
        */
        if(s[i]==t[j])
        {
            i++;
            j++;
        }
        else if(j==0)//第一个字符就不匹配，主串直接移位
        i++;
        else
        {
            j=next[j-1];//转到Next[j]，主串不要动,从这里开始回朔匹配
        }
        if(j==lent)//匹配成功
        {
            index=i-j;
            break;
        }
    }
    return index;
    
}
int main()
{
    char s[MAXSIZE],t[MAXSIZE];
    scanf("%s",s);
    scanf("%s",t);
    int index=KmpSearch(s,t);
    if(index!=-1)
    printf("index=%d",index);
    else 
    printf("'%s'has not been found",t);
    return 0;
}