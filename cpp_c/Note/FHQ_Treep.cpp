#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
typedef struct Node{
    int val;
    struct Node *l,*r;
    int priority;//随机优先级（爸爸>儿子）
    int size;//以我为根有多少节点
    Node(int v): val(v),l(nullptr),r(nullptr),size(1),priority(rand()) {}//初始化，size为1
}Node;

int getsize(Node*u)
{
    return u?u->size:0;//存在返回size，NULL返回0；
}

void sizeupdate(Node* u)// 当我们切断了链接或者连上了新孩子，当前节点的 size 就不对了，需要重新算
{
    if(u!=NULL)
    u->size=getsize(u->l)+getsize(u->r)+1;
}
/*
    Split把以u为root的树切成两半          
    x:<=v;
    y:>v;                                      
*/
void split(Node* &u,int v,Node*&x,Node*&y)//*&为c++特性，可以直接改变指针变量，等价于c/c++的双重指针，把u分成x，y两个单独的树
//*访问结构体只能改变值，**or*&可以改变指针指向
{
    if(!u)//切到空树，返回
    {
        x=nullptr;
        y=x;
        return;
    }

    if(u->val<=v)
    {
        x=u;//访问左树指向了u；
        /*
        问题的关键是：之前的u的右树可能有些大于v，
        按照规矩,这些元素不能随u一起放在左树里面，我们需要切割，
        切完过后，小于v的部分依然挂在u的右边
        大于v的部分需要挂在真正的右树
        */
        split(u->r,v,u->r,y);

    }
    else
    {
        y=u;
        split(u->l,v,x,u->l);
    }
    sizeupdate(u);//每次递归更新u->size
}
Node *merge(Node*x,Node*y)//拼接x，y
{
    if(!x||!y)  return x?x:y;//有一个为空，直接返回另一个
    if(x->priority>y->priority)
    {
        /*
        x比y小，x->l别动
        需要把右儿子和y合并
        */
        x->r=merge(x->r,y);
        sizeupdate(x);
        return x;
    }
    else{
        y->l=merge(x,y->l);//x,y->l；保证顺序
        sizeupdate(y);
        return y;
    }
}
/*
“中序遍历定死顺序，随机优先级决定形态。”
Split（分裂）：是在维护那个**“不变的相对位置”**（BST 性质）。
Merge（合并）：是在利用**“谁做根节点”**（Heap 性质）来通过随机性保持平衡。
*/
Node* Insert(int val,Node *root)
{
    Node*x=nullptr,*y=nullptr;
    split(root,val,x,y);//根节点大树按照val切开
    return merge(merge(x,new Node(val)),y);
}
void Inorder(Node* p)
{
    if(p==nullptr)
    return;
    Inorder(p->l);
    cout<<p->val<<" ";
    Inorder(p->r);
}
Node* remove(int val,Node*root)
{
    Node *x=nullptr,*y=nullptr,*z=nullptr;
    split(root,val,x,z);//x.val<=val z.val>val,保留z;
    split(x,val-1,x,y);//保留x；y是val;
    //由于分割节点时，尽管y有左右，但是y->val==val，也会被切掉，
    if(y)
    {
        Node* old=y;
        y=merge(y->l,y->r);
        delete old;
    }
    return merge(merge(x,y),z);
}
int main()
{
    Node* root = nullptr;
    root = Insert(5, root);
    root = Insert(3, root);
    root = Insert(7, root);
    root = Insert(2, root);
    root = Insert(4, root);
    root = Insert(6, root);
    root = Insert(8, root);
    cout << "Inorder traversal after insertions: ";
    Inorder(root);
    cout << endl;
    root = remove(3, root);
    cout << "Inorder traversal after removing 3: ";
    Inorder(root);
    cout << endl;
    root = remove(7, root);
    cout << "Inorder traversal after removing 7: ";
    Inorder(root);
    cout << endl;
    return 0;
}