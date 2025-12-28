#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int val;
    struct node *next;
}node;
typedef struct{
    int num;
    node *head;
    node *rear;
}LIST;
void Init(LIST* ls)
{
    node *Head=(node*)malloc(sizeof(node));
    Head->val=-404;
    ls->head=Head;
    ls->rear=ls->head;
    ls->head->next=NULL;
    ls->num=0;
}
void Insert(LIST *ls,int n)
{
    node*Newnode=(node*)malloc(sizeof(node));
    Newnode->val=n;
    Newnode->next=NULL;
    ls->rear->next=Newnode;
    ls->rear=Newnode;
    ls->num++;
}
void Delete1(LIST *ls,int x)//非递归删除
{
    node *pre=ls->head;
    node *temp=ls->head->next;
    while(temp!=NULL)
    {
        if(temp->val==x&&temp->next!=NULL)
        {
            node *tmp=temp;
            pre->next=temp->next;
            temp=temp->next;
            free(tmp);
            ls->num--;//删除后pre相对位置不变，pre不动,temp动！！！
        }
        else if(temp->val==x&&temp->next==NULL)//删除尾指针需要单独处理
        {
            ls->rear=pre;
            node *tmp=temp;
            pre->next=temp->next;
            temp=temp->next;
            free(tmp);
            ls->num--;
        }
        else
        pre=temp,temp=temp->next;
    }
}
void deletehelper(node** p,LIST* ls,int x)
{
    node* cur=*p;
    if(cur->next==NULL)
    {
        return;
    }
    if(cur->val==x)
    {
        node *temp=cur;
        *p=(*p)->next;
        /*
        二级指针重要性！！！可以改变前驱节点指针
        p是node->next的地址也就是A->NEXT地址
        *p是node->next也就是B的地址
        赋值操作实质:
        a=10;
        a=20;
        赋值并不是把10改成20
        而是把a的地址的内容改成了20
        即*(&a)=20
        我们类比有
        (*p)=(*p)->next
        即*(&(*P))=(*p)->next
        即*（**p）=……
        即改变了A->next指向的地址，变成了C的地址
        */
        /*
        在链表中，因为 p 已经存放了 A->next 的地址（即 p == & (A->next)），所以：
        左边：*p 等价于 *(& (A->next)) -> 也就是 A->next 这个变量本身。
        右边：(*p)->next -> 等价于 B->next -> 也就是 C 的地址。
       */
        free(temp);
        ls->num--;
        deletehelper(p,ls,x);//检查更新后的当前节点是否应该删除，此时p本身就是node->next的地址
    }
    else
    {
        deletehelper(&(cur->next),ls,x);
    }
}
void Delete2(LIST* ls,int x)//递归删除
{
    deletehelper(&(ls->head->next),ls,x);//从有效的第一个节点开始删除
    //可能删除尾指针，需要进行修补；
    node* temp=ls->head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    ls->rear=temp;

}
void print(LIST* ls)
{
    node *temp=ls->head->next;
    while(temp!=NULL)
    {
        printf("%d ",temp->val);
        temp=temp->next;
    }
}
int main()
{
    LIST ls;
    Init(&ls);
    Insert(&ls,1);
    Insert(&ls,9);
    Insert(&ls,4);
    Insert(&ls,1);
    Insert(&ls,5);
    Insert(&ls,9);
    Insert(&ls,3);
    Delete1(&ls,1);
    print(&ls);
    printf("\n");
    Insert(&ls,3);
    Insert(&ls,5);
    Insert(&ls,2);
    Insert(&ls,3);
    Insert(&ls,4);
    Insert(&ls,3);
    Insert(&ls,2);
    print(&ls);                                        
}