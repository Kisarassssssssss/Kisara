#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string>
using namespace std;
typedef struct LinkNode{
    int val;
    struct LinkNode * next;
}LinkNode;
typedef struct{
    LinkNode* front,*tear;
}LinkQueue;
void InitLQ(LinkQueue* lq,int num)
{
    LinkNode *temp=(LinkNode*)malloc(sizeof(LinkNode));
    temp->val=num;
    temp->next=NULL;
    lq->tear=temp;
    lq->front=temp;
}
void ENq(int num,LinkQueue *lq)
{
    LinkNode *temp=(LinkNode*)malloc(sizeof(LinkNode));
    temp->val=num;
    temp->next=NULL;
    lq->tear->next=temp;
    lq->tear=temp;  
}
int Deq(LinkQueue *lq)
{
    assert(!(lq->front==lq->tear));
    int vals=lq->front->val;
    LinkNode *temp=lq->front;
    lq->front=lq->front->next;
    free(temp);
    return vals;
}
int main()
{
    LinkQueue lq;
    InitLQ(&lq,1);
    ENq(2,&lq);
    ENq(3,&lq);
    ENq(4,&lq);
    cout<<Deq(&lq)<<endl;
    cout<<Deq(&lq)<<endl;
    cout<<Deq(&lq)<<endl;
    cout<<Deq(&lq)<<endl;
    return 0;
}