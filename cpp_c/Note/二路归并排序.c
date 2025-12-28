#include <stdio.h>
#define MAXSIZE 10001
int arr[MAXSIZE]={1,9,2,6,4,3,7,5,8};
void merge(int arr[],int left,int right,int mid)
{
    int l[MAXSIZE], r[MAXSIZE];
    for(int i=left;i<=mid;i++)
        l[i-left]=arr[i];
    for(int j=mid+1;j<=right;j++)
        r[j-mid-1]=arr[j];
    //记录左右数组的下标
    int i=0,j=0,k=left;
    while((i<mid-left+1&&j<right-mid))
    {
        if(l[i]<=r[j])
        {
            arr[k]=l[i];
            i++;
        }
        else
        {
            arr[k]=r[j];
            j++;
        }
        k++;
    }
    while(i < mid-left+1) {
        arr[k] = l[i];
        i++;
        k++;
    }
    
    while(j < right-mid) {
        arr[k] = r[j];
        j++;
        k++;
    }

}
void devide(int arrr[],int left,int right)
{
    if(left>=right)
    return;
    int mid=left+(right-left)/2;//为何不是(left+right)/2,是为了防止数字太大溢出int范围
    devide(arrr,left,mid);
    devide(arrr,mid+1,right);//递归
    merge(arrr,left,right,mid);//合并

}
int main(void)
{
    devide(arr,0,8);
    for(int i=0;i<9;i++)
    {
        printf("%d ",arr[i]);
    }
    return 0;
}