#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node* next;
}node;
typedef struct{
    int num;
    node* head;
}List;
void Init(List *ls,int n)
{
    ls->num=1;
    node *Head=(node*)malloc(sizeof(node));
    node *Newnode=(node*)malloc(sizeof(node));
    Head->data=-404;
    Newnode->data=n;
    Newnode->next=NULL;
    Head->next=Newnode;
    ls->head=Head;
}
void Insert(List *ls,int n)
{
    node*Newnode=(node*)malloc(sizeof(node));
    Newnode->data=n;
    Newnode->next=ls->head->next;
    ls->head->next=Newnode;
    ls->num++;
}
int find(List *ls,int x)
{
    if(x==1)
    {
        printf("%d\n",ls->head->next->data);
        return 1;
    }
    if(ls->num<x)
    return -1;
    else
    {
        node* temp=ls->head->next;
        int sum=1;
        while(temp->next!=NULL)
        {
            if(sum==x)
            {
                printf("%d\n",temp->data);
                return 1;
            }
            else
            temp=temp->next,sum++;
        }
    }
}
int main()
{
    List ls;
    Init(&ls,1);
    Insert(&ls,2);
    Insert(&ls,3);
    Insert(&ls,4);
    Insert(&ls,5);
    Insert(&ls,6);
    int x;
    scanf("%d",&x);
    printf("%d",find(&ls,x));
}