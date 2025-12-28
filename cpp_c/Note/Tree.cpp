#include <iostream>
using namespace std;
#define datatype int
#define MAXSIZE 10001
/*
*    tree的双亲表示法
*/
typedef struct nodeP{
    datatype val;
    int Parent;
}nodeP;
typedef struct TreeP{
    nodeP nodes[MAXSIZE];
    int root,num;//根的位置，节点数
}TreeP;
/*
        tree的孩子表示法
        Ctree T
|
|-- root (根节点在数组中的下标，比如 0)
|-- num (节点总数)
|
|-- nodes[] 数组
    |
    |-- [0] (CTBox)
    |    |-- val: "A"
    |    |-- firstchild ---------> [CTNode] (链表节点)
    |                               |-- child: 1 (代表B在数组的下标)
    |                               |-- Nextchild --> [CTNode]
    |                                                  |-- child: 2 (代表C)
    |                                                  |-- Nextchild --> NULL
    |
    |-- [1] (CTBox)
    |    |-- val: "B"
    |    |-- firstchild --> NULL (B是叶子节点)
    |
    |-- [2] (CTBox) ...
*/
typedef struct CTNode{
    int child;//孩子节点在nodes数组里的下标
    struct CTNode *Nextchild;//同一父亲的下一个孩子
}CTNode;
typedef struct CTBox{
    datatype val;
    CTNode *firstchild;
}CTBox;
typedef struct Ctree{
    CTBox nodes[MAXSIZE];//所有节点的数据和他们的第一个孩节点
    int root,num;
}Ctree;
/*
    孩子兄弟表示法
            A
        /  |  \
        B   C   D
        / \      |
        E   F     G


                A
                /
                B
                / \
                E   C
                \   \
                F   D
                    /
                    G

解释（以A结点为例）：
1. A的 FirstChild -> B (A的第一个孩子)
2. B的 NextSibling -> C (A的第二个孩子，即B的下一个兄弟)
3. C的 NextSibling -> D (A的第三个孩子，即C的下一个兄弟)
4. D的 NextSibling -> NULL (A没有更多孩子了)
*/
typedef struct CSNode{
    datatype val;
    struct CSNode *firstchild,*rightbro;
}CSNode,*CSTree;
/*
    二叉树
    完全二叉树：父取半，子翻倍，对数算深度，编号有奇偶
*/
/*
二叉树的二叉链表结点构造定义
*/
typedef struct BiNode{
    datatype val;
    struct BiNode * lchild,*rchild;
}BiNode,*BiTree;
/*递归算法遍历二叉树*/
void visit(BiNode* T)
{
    printf("%d",T->val);
}
void PreOreder(BiTree R)
{
    if(R==NULL)
    return;

    visit(R);
    //根节点->左树->右树
    PreOreder(R->lchild);
    PreOreder(R->rchild);
} 
void InOreder(BiTree R)
{
    if(R==NULL)
    return;

    PreOreder(R->lchild);
    visit(R);
    //左树->根节点->右树
    
    PreOreder(R->rchild);
} 
void PostOrder(BiTree T){
	if(T != NULL){
		PostOrder(T->lchild);	//递归遍历左子树
		PostOrder(T->rchild);	//递归遍历右子树
		visit(T);	//访问根结点
	}
}
/*非递归遍历二叉树*/
void PreOrderNR(BiTree T)
{
    if(!T) return;
    BiTree stack[MAXSIZE];
    int top=0;
    stack[top]=T;//根节点入栈
    while(top>=0)//只要还有节点
    {
        BiTree p = stack[top--];  // 出栈访问
        visit(p);  // 访问节点
        if(p->rchild)
        stack[++top]=p->rchild;
        if(p->lchild)
        stack[++top]=p->lchild;//由LIFO特性，先进后出，所以
    }
}
void InOrderNR(BiTree T)//左孩子访问完了才能访问根，然后才是右孩子
{
    BiTree stack[MAXSIZE];
    int top=-1;
    BiTree t=T;

    while(t||top>=0)
    {///中序列会出现top小于零的情况，即开始想访问左节点但是又没有访问根节点
    if(t!=NULL)//还没走到左儿子尽头
    {
        stack[++top]=t;
        t=t->lchild;
    }
    else//走到头，退栈访问
    {
        t=stack[top--];//退栈，退到最后会访问父亲节点（因为父亲节点在爷爷节点时已经入栈了）
        visit(t);
        t=t->rchild;
        /*非空向左入栈
        NULL先退栈，访问，在入右栈
        */
    }
    }
}
void PostOrderNR(BiTree T)
{
    BiTree p=T,last=NULL;//last是记录右树是否访问的关键
    BiTree stack[MAXSIZE];
    int top=-1;
    while(p!=NULL||top>=0)
    {
        while(p!=NULL)//左儿子一直访问到底
        {
            stack[++top]=p;
            p=p->lchild;
        }
        //左儿子访问完成，栈中是这条左链的倒序
        if(top>=0)//栈中还有元素，需要继续处理
        {
            BiTree peek=stack[top];
            if(peek->rchild!=NULL&&peek->rchild!=last)//看一下最近的节点有无右节点，并且右边没访问过
            {
                p=peek->rchild;
            }//如果无右节点，或者已经访问过
            else//访问根节点，并标记last
            {
                visit(peek);
                last=peek;
                top--;
            }
        }
    }
}//先向左入栈，碰到右边存在且没访问就入栈，右边不存在或者被访问过再出栈，更新last
/*
    层序遍历FIFO队列实现，保证先遇到的层先被访问，上一层的节点出队时，顺手把下一层的孩子带入队尾
*/
void LevelOrder (BiTree T)
{
    if (T == NULL) return; 
    BiTree p=T;
    BiTree queue[MAXSIZE];
    int head=0,rear=1;
    queue[head]=p;//rear指向下一个可用的空位
    while(head!=rear)
    {
        BiTree temp=queue[head];
        visit(temp);
        head=(head+1)%MAXSIZE;
        if(temp->lchild)
        queue[rear]=temp->lchild,rear=(rear+1)%MAXSIZE;
        if(temp->rchild)
        queue[rear]=temp->rchild,rear=(rear+1)%MAXSIZE;
    }
}
/*
*线索二叉树（对于中序遍历可以大大化简，但是前序后序未必，甚至会更复杂）
*/
typedef struct ThreadNode{
    datatype val;
    struct ThreadNode *rchild,*lchild;
    int ltag,rtag;
}ThreadNode,*ThreadTree;
ThreadTree pre=NULL;//记录上一个访问的节点
/*
    线索化二叉树，使用递归算法
    试做如下规定:若结点有左子树，则其lchild域指示其左孩子，否则令lchild域指示其前驱;
    若结点有右子树，则其rchild指示其右孩子，否则令rchild域指示其后继。
    前驱后继是指的遍历顺序后面的节点，即左子树的最右边的节点，右子树的最左边的节点
    为避免混淆，尚需改变结点结构，增加两个标志域LTag和RTag。
*/
void InThread(ThreadTree T)//将普通二叉树（rtag/ltag未处理）→ 线索二叉树（rtag/ltag已处理）
{
    if(T==NULL) 
    return;
    InThread(T->lchild);//中序，左根右
    if(T->lchild==NULL)
    {
        T->lchild=pre;
        T->ltag=1;
    }//如果左儿子为空，记录前驱
    if(pre!=NULL&&pre->rchild==NULL)
    {
        pre->rchild=T;
        pre->rtag=1;
    }//如果pre右儿子为空，记录后继T；
    pre=T;
    InThread(T->rchild);
}
ThreadTree FindFirst(ThreadTree T)//向左找到第一个节点，
{
    ThreadTree t=T;
    while(t->lchild!=NULL&&t->ltag==0)//有左孩子并且左孩子是真的孩子，不是前驱指针
    {
        t=t->lchild;
    }
    return t;
}
ThreadTree NextNode(ThreadTree T)
{
    if(T->rtag==1)
    {
        return T->rchild;
    }
    else
    {
        return FindFirst(T->rchild);//右分支的第一个节点就是后继节点
    }
}
ThreadTree FindLast(ThreadTree T) 
{
    if (T==NULL) 
    return NULL;   
    ThreadTree p =T;
    // 一直向右走，直到没有右孩子（rtag==1）
    while (p->rtag==0&&p->rchild!=NULL) 
    {
        p=p->rchild;
    }
    return p;
}
ThreadTree FindPre(ThreadTree t)
{

    if(t->ltag==1)
    {
        if(t->lchild==NULL) return NULL;
    printf("%d",t->lchild->val);
    return t->lchild;
    }
    else
    {
        return FindLast(t->lchild);
    }
}
void InOrderTravelSal(ThreadTree T)
{
    ThreadTree t=FindFirst(T);
    while(t!=NULL)
    {
        printf("%d ",t->val);
        t=NextNode(t);
    }
}
/*
中序线索二叉树总结
1. 核心设计思想
利用空指针：在 n个节点的二叉树中，共有2n个指针域，
其中只有 n−1个用来指向子节点，
剩余 n+1个空指针。线索二叉树将这些空指针利用起来，存储节点在遍历中的前驱和后继信息，从而把树形结构转化为“线性”结构，方便遍历。
2. 存储标志位 (Tag) 的含义
为了区分 lchild 和 rchild 到底指向的是孩子还是线索，引入了两个标志位：
ltag:
0: lchild 指向左孩子。
1: lchild 指向前驱（线索）。
rtag:
0: rchild 指向右孩子。
1: rchild 指向后继（线索）。
3. 找“前驱”与“后继”的逻辑（核心）
这是你代码中最关键的部分，也是考研或面试的重点。
A. 找后继 (NextNode)
原则：中序遍历的顺序是 左 -> 根 -> 右。根节点的后继是右子树的第一个访问节点。
若 rtag == 1：直接通过线索找到后继。
return T->rchild;
若 rtag == 0（有右子树）：后继是右子树中最左下的节点。
return FindFirst(T->rchild);
B. 找前驱 (FindPre)
原则：中序遍历的顺序是 左 -> 根 -> 右。根节点的前驱是左子树的最后访问的节点。
若 ltag == 1：直接通过线索找到前驱。
return T->lchild;
若 ltag == 0（有左子树）：前驱是左子树中最右下的节点。
return FindLast(T->lchild);
4. 线索化过程 (InThread)
这是一个一边中序遍历，一边修改指针的过程。需要一个全局变量 pre 来记录刚刚访问过的节点。
算法流程：
递归线索化左子树。
处理当前节点 T 与 pre 的关系：
T 的左边：如果 T 没有左孩子，T->lchild 指向 pre（建立前驱线索）。
pre 的右边：如果 pre 没有右孩子，pre->rchild 指向 T（建立后继线索）。注意：这是在访问 T 时，才去修改 pre 的右指针。
更新 pre = T。
递归线索化右子树。
代码对应：
code
C
// 补前驱
if(T->lchild==NULL) { T->lchild=pre; T->ltag=1; }
// 补后继 (注意判空)
if(pre!=NULL && pre->rchild==NULL) { pre->rchild=T; pre->rtag=1; }
pre=T; // 移动指针
5. 辅助函数解析
函数名	作用	逻辑简述
FindFirst	找中序遍历的起点	一直往左走，直到 ltag==1（没有左孩子了）。
FindLast	找中序遍历的终点	一直往右走，直到 rtag==1（没有右孩子了）。通常用于找前驱时定位左子树的最右节点。
NextNode	找下一个节点	有线索看线索，没线索找右子树的最左节点（即 FindFirst(T->rchild)）。
InOrderTravelSal	非递归遍历	1. 找到起点 FindFirst。<br>2. 循环调用 NextNode 直到 NULL。
6. 优缺点对比
优点：
利用了空闲内存。
找前驱和后继非常方便（尤其是后继）
遍历时不需要使用栈（Stack）也不需要递归，空间复杂度为 O(1)。
缺点：
节点的插入和删除变得复杂，因为需要维护线索。
7. 一句话口诀
线索看标志，子树找极值。
有线索（tag=1），直接走；
无线索（tag=0），找右子树的最左（后继），或左子树的最右（前驱）。
*/


/*
    树的遍历
    根据树和二叉树的转换，儿子向左，兄弟向右；
    只需要前序依次遍历即可；保证根左右的顺序；
*/
int main()
{
    
}