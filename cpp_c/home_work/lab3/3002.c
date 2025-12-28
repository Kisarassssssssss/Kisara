#include <stdio.h>
int n,data[10001]={0};
int cs(int front,int rear)
{
    if(front==rear)
    return data[front];
    int s=data[front]-cs(front+1,rear);//本轮得分减去对方净胜分==自己净胜分
    int t=data[rear]-cs(front,rear-1);
    if(s>=t)
    return s;
    else
    return t;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&data[i]);
    }
    int rear=n-1;
    int front=0;
    if(cs(0,n-1)>=0)
    printf("true");
    else 
    printf("false");
    return 0;

}