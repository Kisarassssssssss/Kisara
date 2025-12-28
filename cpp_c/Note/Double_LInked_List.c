#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct LTNode{
    int data;
    struct LTNode* pre;//ps：初始化时这个LTNode还没有完成定义，所以只能用struct LTNode*
    struct LTNode* next;
}LTNode;


void SetLTNode(LTNode* LT, int val);
LTNode* CreateLTNode(int val);
void LTInit(LTNode** LT);
void LTDheadInsert(LTNode* LT, int val);
void LTtailInsert(LTNode* LT, int val);
void PrintList(LTNode* LT);
void DELETE(LTNode* LT, int i);
void DestroyList(LTNode* LT);

LTNode* CreateLTNode(int val)//创建节点
{
    LTNode* newNode=(LTNode*)malloc(sizeof(LTNode));
    assert(newNode);
    SetLTNode(newNode,val);
    newNode->next=NULL;
    newNode->pre=NULL;
    return newNode;
}
void SetLTNode(LTNode* LT, int val)//设置节点
{
    assert(LT);
    LT->data=val;
}
void LTInit(LTNode **LT)//初始化双向链表，设置哨兵节点,传入的是LT的地址的指针
{
    assert(LT);
    *LT=(LTNode*)malloc(sizeof(LTNode));//分配内存
    assert(*LT);
    SetLTNode((*LT),-1);//设置哨兵节点的值为-1
    (*LT)->next=*LT;
    (*LT)->pre=*LT;
}
void LTDheadInsert(LTNode* LT,int val)//头插法
{
    assert(LT);
    LTNode* newNode=CreateLTNode(val);
    newNode->next=LT->next;//LT指向哨兵节点，LT->next指向原来第一个节点
    newNode->pre=LT;//新节点的头指向哨兵
    LT->next->pre=newNode;//原来第一个节点的pre指向新节点
    LT->next=newNode;//哨兵节点的next指向新节点
}
void LTtailInsert(LTNode* LT,int val)//尾插法
{
    assert(LT);
    LTNode* newNode=CreateLTNode(val);
    newNode->pre=LT->pre;//LT指向哨兵节点，LT->pre指向原来最后一个节点,双向循环链表
    newNode->next=LT;//新节点的next指向哨兵
    LT->pre->next=newNode;//原来最后一个节点的next指向新节点
    LT->pre=newNode;//哨兵节点的pre指向新节点
}

void PrintList(LTNode* LT)
{
    assert(LT);
    LTNode* ls=LT->next;
    while(ls!=LT)
    {
        printf("%d ",ls->data);
        ls=ls->next;
    }
    printf("\n");
}
void Insert(LTNode *LT,int i,int val)
{
    assert(LT);
    LTNode* ls=LT->next;
    int cnt=1;
    while(ls!=LT&&cnt<i)
    {
        cnt++;
        ls=ls->next;
    }
    LTNode* nls=CreateLTNode(val);
    LTNode* pree=ls->pre;
    LTNode* next=ls;
    pree->next=nls;
    nls->pre=pree;
    nls->next=next;
    next->pre=nls;

}
void DELETE(LTNode*LT,int i)
{
    assert(LT);
    LTNode* ls=LT->next;
    int cnt=1;
    while(ls!=LT&&cnt<i)
    {
        ls=ls->next;
        cnt++;
    
    }
    LTNode* pree=ls->pre;
    LTNode* nextt=ls->next;
    pree->next=nextt;
    nextt->pre=pree;
    free(ls);
    //找到第i个节点，记录上一个和下一个节点的地址，直接改变上下节点的指针指向，释放当前节点
}
/*
使用了动态内存分配的就是堆分配，其他则是栈分配；堆分配一般和地址传递一起使用，对于跨函数使用的数据结构，
一般都用堆分配+地址传递的方式进行处理；而栈分配一般用于函数内部的临时变量等，这里为了保证数据结构的跨函数使用，使用了堆分配。即传入指针的指针。方便使用malloc分配指针的地址
链表是用结构体指针连接起来的多个结构体。结构体存储数据，结构体指针建立关系
*/
int main()
{
    LTNode* LT;
    LTInit(&LT);
    LTtailInsert(LT,1);
    LTtailInsert(LT,2);
    LTtailInsert(LT,3);
    PrintList(LT);
    DELETE(LT,2);
    Insert(LT,2,7);
    Insert(LT,1,9);
    PrintList(LT);
    
    return 0;
}