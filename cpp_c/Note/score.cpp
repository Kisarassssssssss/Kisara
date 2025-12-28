#include <stdio.h>
#define MAX 41
int a[MAX];
int i=1;
void f()
{
    double average=0;
    for (int j=1;j<=i;j++)
    {
        average+=a[j];
    }
    average/=i;
    int count=0;
    for (int j=1;j<=i;j++)
    {
        if (a[j]>average)
        {
            count++;
        }
    }
    printf("%d",count);
}
int main()
{
   
    scanf("%d",&a[i]);
    while (a[i]>0)
    {
        i++;
        scanf("%d",&a[i]);
    }
    i--;
    f();
    return 0;
}