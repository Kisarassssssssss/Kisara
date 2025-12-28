#include <iostream>
#include <algorithm>
using namespace std;
typedef struct Node{
    int val;;
    struct Node *l,*r;
    int height;
    Node(int v):val(v),l(nullptr),r(nullptr),height(1){}
};
int getheight(Node *p)
{
    return p?p->height:0;
}
int getbalance(Node *p)//左树相对高度减去右树相对高度
{
    return p?(getheight(p->l)-getheight(p->r)):0;
}
void update_height(Node* p)
{
    if(p)
    p->height=max(getheight(p->l),getheight(p->r))+1;
}
/*
    tip1:RR右旋
         y
        /
       x
      / 
     z
    旋转为：
        x
       / \
      z   y
    ps:原来y，x是有右子树的，但是x的左边新插入了一个一个元素，导致y的左边高度比右边大2
*/
Node* RightRotate(Node *y)
{
    Node *x=y->l;
    Node *z=x->r;
    //y的左边没有挂载，x的右边多了一个挂载
    x->r=y;
    y->l=z;
    //x,y的挂载发生了变化，需要更新高度
    update_height(y);
    update_height(x);
    return x;
}
/*
    tip2:左旋
         y
          \
           x
            \ 
             z
    旋转为：
        x
       / \
      y   z
*/
Node *LeftRotate(Node *y)
{
    Node *x=y->r;
    Node *T1=x->l;
    x->l=y;
    y->r=T1;
    update_height(y);
    update_height(x);
    return x;
}
Node *Rebalance(Node *root)
{
    update_height(root);
    int bf=getbalance(root);
    if(bf>1)//左树更重
    {
        //左孩子左树重，直接右旋
        //左孩子右树重，左旋孩子，右旋自己
        if(getbalance(root->l)<0)
        root->l=LeftRotate(root->l);
        
        return RightRotate(root);

    }
    if(bf<-1)
    {
        if(getbalance(root->r)>0)
        root->r=RightRotate(root->r);
        return LeftRotate(root);
    }
    return root;//平衡就直接返回
}
Node *InsertAVL(Node* r,int val)
{
    if(r==nullptr)//找到了插入位置
    {
        return new Node(val);
    }
    if(val<r->val)
    r->l=InsertAVL(r->l,val);
    if(val>r->val)
    r->r=InsertAVL(r->r,val);
    else if(val==r->val)
    return r;//找到了一样的，直接返回

    return Rebalance(r);//实现平衡
}
Node *Remove(Node *r,int val)
{
    if(r==nullptr)
    return nullptr;
    if(r->val>val)
    {
        r->l=Remove(r->l,val);
    }
    else if(r->val<val)
    {
        r->r=Remove(r->r,val);
    }
    else
    {
        if(r->l==nullptr)
        {
            Node *temp=r;
            r=r->r;
            delete temp;
        }
        else if(r->r==nullptr)
        {
            Node *temp=r;
            r=r->l;
            delete temp;
        }
        else
        {
            Node *successor=r->r;
            while(successor->l)
            {
                successor=successor->l;
            }
            r->val=successor->val;
            r->r=Remove(r->r,successor->val);
        }
    }
    return Rebalance(r);
}
int main()
{

}