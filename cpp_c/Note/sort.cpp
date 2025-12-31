#include <iostream>
#include <vector>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;
/*
    每次将最大值冒到最右边；
    分为左边i个无序数组和右边n-i个有序；
    时间复杂度O(n^2)
*/
void BubbleSort(int *a,int n)
{
    int end=n-1;
    while(end)
    {
        int exchangeFlag=0;
        for(int i=0;i<end;i++)
        {
            if(a[i]>a[i+1])
            {
                int t=a[i];
                a[i]=a[i+1];
                a[i+1]=t;
                exchangeFlag++;
            }
        }
        if(exchangeFlag==0)
        break;
        end--;
    }
}
/*
    插入排序
    for(A,B,C)
    {
        D;
    }
    判断B->执行D->执行C(更新/减少)
*/
void InsertSort(int *a,int n)
{
    for(int i=1;i<n;i++)
    {
        if(a[i]>a[i-1])
        continue;
        int t=a[i];
        int j;
        for(j=i-1;j>=0&&a[j]<t;j--)
        {
            a[j+1]=a[j];
        }
        a[j+1]=t;//这里减了一次，要加回来；
    }
}
void SelectSort(int *a,int n)
{
    for(int i=0;i<n;i++)
    {
        int minIndex=i;
        int j;
        for(int j=i;j<n;j++)
        {
            if(a[j]<a[minIndex])
            minIndex=j;
        }
        int tmp=a[minIndex];
        a[minIndex]=a[i];
        a[i]=tmp;
    }
}
/*
    希尔排序(插入排序改良版)：基本有序的数列插入排序较快；
    希尔排序将数列分为增量为h的子数列；
    1.所有距离为h的元素化为一组；
    2.每一组进行直接插入排序；
    3.缩小增量h，继续进行
    4.h=1,进行标准插入排序(基本有序，速度极快)
    普通的插入排序就像在狭窄的走廊搬箱子，如果你要把最后的箱子搬到最前面，你必须经过中间所有的箱子，效率很低。
    希尔排序则是先在走廊上挖几个“虫洞”（增量 Gap），让箱子可以跨过中间的人，直接“瞬移”到前面。等大部分箱子都大致归位了，最后再进行一次微调。
*/
void ShellSort(vector<int>& arr)
{
    int n=arr.size();
    for(int h=n/2;h>0;h/=2)//增量依次递减
    {
        for(int i=h;i<n;i++)
        {
            int tmp=arr[i];
            int j;
            for(j=i;j>=h&&arr[j-h]>tmp;j-=h)
            {
                arr[j]=arr[j-h];//前面往后挪，直到找到合适的插入位置
            }
            arr[j]=tmp;
        }
    }
}
/*
    堆排序：实质利用了树
    采用大顶堆，根节点大于等于左右节点
    左儿子：2i+1；右儿子2i+2
    1.建堆将无序数组构造成一个大顶堆。此时，最大的数已经换到了数组的第 0 个位置。
    2.排序：踢出堆顶，对剩下元素调整形成大顶堆，重复过程；
    3.堆化（下沉）
    假设某个节点的左右子树已经是堆，但该节点本身比孩子小，我们需要让它下沉到正确的位置。
    比较父节点 A 和它的两个孩子 B、C。
    如果孩子中有一个比 A 大，就把 A 和最大的那个孩子交换。
    A 下沉后，可能还会破坏下面的子树，所以继续向下比较并下沉，直到 A 比孩子都大，或者沉到了叶子节点。
*/
void heapify(vector<int>& arr,int n,int i)//堆的大小，下沉节点
{
    int lar=i;//假设当前最大
    int l=2*i+1;//左孩子 
    int r=2*i+2;
    if(l<n&&arr[l]>arr[lar])
    {
        lar=l;
    }
    if(r<n&&arr[r]>arr[lar])
    {
        lar=r;
    }
    if(lar!=i)
    {
        swap(arr[lar],arr[i]);
        heapify(arr,n,lar);//继续下沉
    }
}
void heapSort(vector<int>& arr)
{
    int n=arr.size();
    for(int i=n/2-1;i>=0;i--)//从最后一个非叶子节点开始调整
    {
        heapify(arr,n,i);//调整为大顶堆
    } 
    for(int i=n-1;i>0;i--)
    {
        swap(arr[0],arr[i]);//把0（最大节点）拿到队尾，排好序
        heapify(arr,i,0);//继续调整
    }
}
int main()
{
    
}