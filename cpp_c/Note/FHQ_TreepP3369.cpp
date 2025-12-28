#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
typedef struct Node{
    int val;
    struct Node *l,*r;
    int priority;
    int size;
    Node(int v):val(v),l(nullptr),r(nullptr),priority(rand()),size(1){}
}Node;
int getsize(Node *root)
{
    return root?root->size:0;
}
void sizeupdate(Node*root)
{
    if(root)
    root->size=getsize(root->l)+getsize(root->r)+1;
}
void split(Node*&r,int val,Node*&x,Node*&y)
{
    if(r==nullptr)
    {
        x=nullptr;
        y=nullptr;
        return;
    }
    if(r->val<=val)
    {
        x=r;
        split(x->r,val,x->r,y);
    }
    else
    {
        y=r;
        split(y->l,val,x,y->l);
    }
    sizeupdate(r);
}
Node *merge(Node *x,Node *y)
{
    if(!x||!y)
    return x?x:y;
    if(x->priority>=y->priority)
    {
        x->r=merge(x->r,y);
        sizeupdate(x);
        return x;
    }
    else
    {
        y->l=merge(x,y->l);
        sizeupdate(y);
        return y;
    }
}
Node *Insert(int val,Node *r)
{
    Node*x=nullptr,*y=nullptr;
    split(r,val,x,y);
    return merge(merge(x,new Node(val)),y);
}
Node *remove(int val,Node *r)
{
    Node*x=nullptr,*y=nullptr,*z=nullptr;
    split(r,val,x,z);
    split(x,val-1,x,y);
    if(y)
    {
        Node* old=y;
        y=merge(y->l,y->r);
        delete old;
    }
    return merge(merge(x,y),z);
}
int NumofSmaller(int val, Node *&r) 
{
    Node *x=nullptr,*y=nullptr;
    split(r,val-1,x,y);
    int ans=getsize(x);   
    r=merge(x,y);
    return ans+1;
}

int Inorder(Node *r, int x) 
{
    int leftsize=getsize(r->l);
    if(x==leftsize+1)
    return r->val;
    else if(x<=leftsize)
    return Inorder(r->l,x);
    return Inorder(r->r,x-1-leftsize);
}

int Findpre(Node *&r,int tar)
{
    Node *x=nullptr,*y=nullptr;
    split(r,tar-1,x,y);
    if(x==nullptr)
    {
        r = merge(x, y); 
        return -2147483647; 
    }
    Node *temp=x;
    while(temp->r)
    {
        temp=temp->r;
    }
    r=merge(x,y);
    return temp->val;
}

int Findnext(Node *r,int tar)
{
    Node *x=nullptr,*y=nullptr;
    split(r,tar,x,y);
    if (y == nullptr) {
        r = merge(x, y); 
        return 2147483647; 
    }
    Node *temp=y;
    while(temp->l)
    {
        temp=temp->l;
    }
    r=merge(x,y);
    return temp->val;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand((unsigned)time(NULL));
    int n;
    cin>>n;
    Node *root=nullptr;
    for(int i=0;i<n;i++)
    {
        int step;
        cin>>step;
        int val;
        cin>>val;
        switch (step)
        {
        case 1:{
            root=Insert(val,root);
            break;
        }
        case 2:{
            root=remove(val,root);
            break;
        }
        case 3:{
            cout<<NumofSmaller(val,root)<<endl;
            break;
        }
        case 4:{
            cout<<Inorder(root,val)<<endl;
            break;
        }
        case 5:{
            cout<<Findpre(root,val)<<endl;
            break;
        }
        case 6:{
            cout<<Findnext(root,val)<<endl;
            break;
        }
        default:
            break;
        }
    }
    return 0;
}