#include <iostream>
#include <queue>
#include <string>
#include <assert.h>
using namespace std;
#define MAX_QUEUE_SIZE 101
typedef struct{
    int data[MAX_QUEUE_SIZE];
    int front,rear;
}SeaQueue;
SeaQueue Sq;
//循环队列   先入队尾，出队出队头，rear指向队尾下一个下标
void SeaQueueInit(SeaQueue *q)
{
    q->rear=0;
    q->front=q->rear;
}
bool Isempty(SeaQueue *q)
{
    return q->front==q->rear;
}
void Enq(SeaQueue *q,int val)
{
    if(q->rear==(q->front-1+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE)
    {
        printf("error");
        exit(-1);
    }
    q->data[(q->rear)%MAX_QUEUE_SIZE]=val;
    q->rear++;

}
int Deq(SeaQueue *q)
{
    assert(!Isempty(q));
    int tem=q->data[(q->front)];
    q->front=(q->front+1)%MAX_QUEUE_SIZE;
    return tem;


}