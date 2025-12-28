#include <stdio.h>
int n;
int a[11][11];
void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
void Transpose(int a[11][11], int n)
{
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            swap(&a[i][j],&a[j][i]);
        }
    }   
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
   Transpose(a,n);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}