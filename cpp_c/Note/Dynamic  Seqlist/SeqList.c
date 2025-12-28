#include <stdio.h>
#include <stdlib.h>
#include "SeqList.h"
#include  <assert.h>
#define  SeqDataType int
typedef struct
{
    SeqDataType *arr;
    int size;//当前空间大小
    int capacity;//当前容量大小
}SL;
void SLInit(SL* sl)//初始化
{
    assert(sl);
    sl->arr = NULL;
    sl->size = 0;
    sl->capacity = 0;
}
void SLDestroy(SL* sl)
{
    assert(sl);
    free(sl->arr);
    sl->arr = NULL;
    sl->size = 0;
    sl->capacity = 0;
}
void SLCheckCapacity(SL* sl)
{
    assert(sl);
    if (sl->size >= sl->capacity)
    {
        int newcapacity = sl->capacity == 0 ? 4 : sl->capacity * 2;
        SeqDataType* newarr = (SeqDataType*)realloc(sl->arr, sizeof(SeqDataType) * newcapacity);
        if (newarr == NULL)
        {
            perror("realloc fail");
            exit(-1);
        }
        sl->arr = newarr;
        sl->capacity = newcapacity;
    }
}
void SLInsert(SL* sl,int pos,SeqDataType data)
{
    assert(sl);
    assert(pos>=0&&pos<=sl->size);
    SLCheckCapacity(sl);
    for(int i=sl->size;i>pos;i--)
    {
        sl->arr[i]=sl->arr[i-1];
    }
    sl->arr[pos]=data;
    sl->size++;
}
int main()
{

}