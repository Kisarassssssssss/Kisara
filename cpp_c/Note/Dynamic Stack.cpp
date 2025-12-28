#include <stdio.h>
#include <assert.h>
typedef struct{
    int *a;
    int top;
    int cap;
}DS;
void StackIint(DS* ds)//初始化
{
    assert(ds);
    ds->a=NULL;
    ds->top=1;
    ds->cap=0;
}
void CheckCap(DS * ds)//检查并扩容
{
    assert(ds);
    
    if(ds->top>=ds->cap)
    {
        int ncap=ds->cap==0?4:ds->cap*2;
        int *tmp=(int*)realloc(ds->a,sizeof(int)*ncap);
        if(tmp==NULL)
        {
            printf("error");
            exit(-1);
        }
        ds->a=tmp;
        ds->cap=ncap;//更新最大容量

    }
}
void PushStack(DS* ds,int dt)
{
    CheckCap(ds);
    ds->a[ds->top++]=dt;//先将dt压入栈顶，然后top++，方便下一次压栈；
}
void PopStach(DS*ds)
{
    assert(ds);
    ds->top--;
}
int TopStack(DS* ds)//a本身指向的首地址没有改变，通过数组寻访安全高效//
{
    assert(ds);
    assert(ds->a!=NULL);
    return ds->a[ds->top];//a本身指向的首地址没有改变，通过数组寻访安全高效//
}

int main()
{


}