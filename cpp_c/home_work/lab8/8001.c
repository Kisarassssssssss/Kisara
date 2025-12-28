#include <stdio.h>
void sort_interest(int *arr, int n) //插入排序
{
    for(int i=1;i<n;i++)
    {
        int ind=arr[i];
        int j=i-1;
        while(arr[j]<ind)
        {
            arr[j+1]=arr[j];//边找边移位
            j--;
        }
        arr[j+1]=ind;
    }
}
int main()
{
    int n;
    int arr[101]={0};
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    sort_interest(arr, n);
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    
}