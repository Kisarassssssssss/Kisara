#include <stdio.h>
/*
    二叉排序树(也称二叉查找树)或者是一棵空树，或者是具有下列特性的二叉树:
    若左子树非空，则左子树上所有结点的值均小于根结点的值。
    若右子树非空，则右子树上所有结点的值均大于根结点的值。
    左、右子树也分别是一棵二叉排序树。
    左节点值小于根小于右节点值
*/
typedef struct BiNode{
    int val;
    struct BiNode* lchild,*rchild;
}BiNode,*BiTree;
BiTree SearchBST(BiTree T,int x)
{
    BiTree p=T;
    while(p!=NULL&&p->val!=x)
    {
        if(p->val>x)
        {
            p=p->lchild;
        }
        if(p->val<x)
        {
            p=p->rchild;
        }
    }
    return p;//要么没找到NULL，要么找到p；
}
BiTree Insert(BiTree T,int x)
{
    BiTree root=T;
    if(T==NULL)//空位可以插入
    {
    BiTree res=(BiTree)malloc(sizeof(BiNode));
    res->val=x;
    return res;
    }
    if(T->val>x)
    {
        root=Insert(root->lchild,x);
    }
    if(T->val<x)
    {
        root=Insert(root->rchild,x);
    }
    return root;//返回修改后的root节点

}
BiTree FindMin(BiTree T)
{
    BiTree p=T;
    while(p->lchild!=NULL)
    p=p->lchild;
    return p;
}
BiTree DeleteBTS(BiTree T,int x)
{
    if(T==NULL) return NULL;
    if(x<T->val)
    {
        T->lchild=DeleteBTS(T->lchild,x);//去左边删，更新左孩子
        return T;
    }
    if(x>T->rchild)
    {
        T->rchild=DeleteBTS(T->rchild,x);//去右边删，更新右孩子
        return T;
    }
    //找到孩子
    else
    {
        /*
        version1:至多一个孩子
        */
        if(T->lchild==NULL)
        {
            BiTree temp=T->rchild;//保留右边孩子
            free(T);
            return temp;
        }
        else if(T->rchild==NULL)
        {
            BiTree temp=T->lchild;//保留右边孩子
            free(T);
            return temp;
        }
        else//左右孩子都有，偷梁换柱
        {
            BiTree successor=FindMin(T->rchild);//找一个后继节点；
            T->val=successor->val;//篡位（仅仅是复制值，身份还没变;
            // 3. 灭口（去右子树里，把那个接班人的旧身躯删掉）
            // 这一步递归非常关键，它会去处理那个“原来的 successor”
            T->rchild=DeleteBTS(T,x);
        }
        /*
        50   <-- 【待删除目标】
       /  \
     30    70
          /  \
        60    80
          \
           65


           60   <-- 【现在的 50 变成了 60】
       /  \
     30    70
          /  \
        60    80  <-- 【原来的 60 还在】
          \
           65


           60
       /  \
     30    70
          /  \
        65    80
        */
    }
    return T;
}
int main()
{

}