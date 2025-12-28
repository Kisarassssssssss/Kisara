#include <bits/stdc++.h>
using namespace std;
struct node {
    int val;
    struct node* next;
};
node *first=NULL;
int acc=0;
struct node *searchlist(struct node* list,int n)//查找节点,返回查找次数;
{
    struct node* goalNode;
    for(goalNode=list;goalNode->next!=NULL;goalNode=goalNode->next)
    {
           acc++;
        if(goalNode->val==n)
        {
            return goalNode;
        }
     
    }
    return NULL;

}
struct node *addtolist(struct node* list,int n){
    node *new_node;
    new_node=(struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
printf("Error: malloc failed in add_to list\n");
exit(EXIT_FAILURE);
}
    new_node->val=n;
    new_node->next=list;
    return new_node;
    //头插法，新的链节在前面。
   // 执行前first指向null；
    //执行后first指向10再指向null
    //first  → [val:10, next:NULL]
}
struct node* delete_node(struct node* list,int n)//删除链表first → [val:3, next:] → [val:8, next:] → [val:5, next:NULL]
                                                                    //   ↑              ↑              ↑
                                                                 //     pre            cur           cur->next
{
    struct node* cur,* pre;
    if(list!=NULL&&list->val==n)
    {
        list=list->next;
        return list;
    }
    for(cur=list,pre=NULL;cur!=NULL;pre=cur,cur=cur->next)
    {
        if(cur->val==n)
        {
            pre->next=cur->next;
            free(cur);
            return list;
        }
    }
    return list;


}
int main(void)
{
    int aa[100001];
    int a;
    int i=0;
    cin>>a;
    while(a!=0)
    {
        
        aa[i++]=a;
         first = addtolist(first, a);
         cin>>a;
    }
    cin>>a;
    searchlist(first,a);
    cout<<endl<<acc<<endl;
    first=delete_node(first,a);
    struct node* p=searchlist(first,a);
    if(p==NULL)
    {
        cout<<"DELETE successfully"<<endl;
        exit(1);
    }
    else
    {
        cout<<"STILL EXIST"<<endl;
        exit(1);
    }
    return 0;
   
}