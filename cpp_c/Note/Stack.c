#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAXSIZE 100001
/*
栈的顺序存储实现（数组）
*/
typedef struct{
    int top;
    int val[MAXSIZE];
}SqStack;
void Init(SqStack *s)
{
    s->top=-1;
}
void Push(SqStack *s,int sum)
{
    assert(s->top<=MAXSIZE-1);
    s-> val[++s->top]=sum;
}
int Pop(SqStack *s)
{
    assert(s->top<=MAXSIZE-1);
    int linm=s->val[s->top];//数组元素清理与否都可以，因为后续再入栈可以覆盖
    s->top--;
    return linm;
}
/*
共享栈
*/
typedef struct{
    int val[MAXSIZE];
    int top1;
    int top2;
}SqStack2;
void Init2(SqStack2 *s)
{
    s->top1=-1;
    s->top2=MAXSIZE;
}//初始化共享栈
void Push2(SqStack2 *s,int sum,int stacknum)
{
    assert(s->top1<s->top2-1);
    if(stacknum==1)
        s->val[++s->top1]=sum;
    else if(stacknum==2)
        s->val[--s->top2]=sum;
}
int Pop2(SqStack2 *s,int stacknum)
{
    int linm;
    if(stacknum==1)
    {
        assert(s->top1!=-1);
        linm=s->val[s->top1];
        s->top1--;
    }
    else if(stacknum==2)
    {
        assert(s->top2!=MAXSIZE);           
        linm=s->val[s->top2];
        s->top2++;
    }
    return linm;
}
/*
栈的链式存储实现
每一个节点指向上一个节点，栈顶指针指向栈顶节点
*/
typedef struct StackNode{
    int dada;
    struct StackNode* next;
}StackNode; //栈结点结构体
typedef struct{
    StackNode* top;//栈顶指针
    int size;//栈的当前元素个数
}LinkStack; //栈结构体
void InitLinkStack(LinkStack *s)
{
    s->top=NULL;
    s->size=0;
}

void PushLinkStack(LinkStack *s,int sum)
{
    StackNode* node=(StackNode*)malloc(sizeof(StackNode));
    node->dada=sum;
    node->next=s->top;//新结点指向栈顶结点
    s->top=node;//栈顶指针指向新结点
    s->size++;
}
/*
执行前：
s->top → [原栈顶节点] → [其他节点] → ... → [栈底] → NULL

执行 node->next = s->top：
node → [新数据] → [原栈顶节点] → [其他节点] → ... → NULL
              ↑
           s->top 还指向原栈顶

执行 s->top = node：
s->top → [新数据] → [原栈顶节点] → [其他节点] → ... → NULL
*/
void popLinkStack(LinkStack *s)
{
    assert(s->size!=0);
    StackNode* node=s->top;//保存栈顶结点指针
    int linm=node->dada;
    s->top=node->next;//栈顶指针指向下一个结点
    free(node);//释放原栈顶结点
    s->size--;
    return linm;
}
int main(void)
{
    SqStack s;
    SqStack2 s1;
}
