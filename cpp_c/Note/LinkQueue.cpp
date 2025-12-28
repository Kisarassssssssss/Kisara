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
    LinkNode* front,*rear;
}LinkQueue;
void InitLQ(LinkQueue* lq)//申请头节点
{
    LinkNode *head = (LinkNode*)malloc(sizeof(LinkNode));
    head->next = NULL;
    lq->rear=head;
    lq->front=head;
}
void ENq(int num,LinkQueue *lq)
{
    LinkNode *temp=(LinkNode*)malloc(sizeof(LinkNode));
    temp->val=num;
    temp->next=NULL;
    lq->rear->next=temp;
    lq->rear=temp;  
}
//front是头节点，front的next是队首
int Deq(LinkQueue *lq)
{
    if(lq->front == lq->rear) 
    {
        cout << "Queue is Empty!" << endl;
        return -1; 
    }
    int vals=lq->front->next->val;
    LinkNode *temp=lq->front->next;
    lq->front->next=lq->front->next->next;
    //如果直接删了，front->next是野指针！！！必须要把rear指向front
    if (lq->rear == temp) {
        lq->rear = lq->front;
    }
    free(temp);
    return vals;
}
int main()
{
    LinkQueue lq;
    InitLQ(&lq);
    ENq(1,&lq);
    ENq(2,&lq);
    ENq(3,&lq);
    ENq(4,&lq);
    ENq(5,&lq);
    cout<<Deq(&lq)<<endl;
    cout<<Deq(&lq)<<endl;
    cout<<Deq(&lq)<<endl;
    cout<<Deq(&lq)<<endl;
    return 0;
}