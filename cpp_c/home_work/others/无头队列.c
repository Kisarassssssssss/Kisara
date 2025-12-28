#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
typedef struct LinkNode{
    int val;
    struct LinkNode * next;
}LinkNode;
typedef struct{
    LinkNode* front,*rear;
}LinkQueue;
void InitLQ(LinkQueue* lq)
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
int Deq(LinkQueue *lq)
{
    if(lq->front == lq->rear) 
    {
        return -1; 
    }
    int vals=lq->front->next->val;
    LinkNode *temp=lq->front->next;
    lq->front->next=lq->front->next->next;
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
    printf("%d",Deq(&lq));
    printf("%d",Deq(&lq));
    printf("%d",Deq(&lq));
    printf("%d",Deq(&lq));
    return 0;
}