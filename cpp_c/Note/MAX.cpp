#include <stdio.h>
int max0;
void Max(int a,int b)
{
    if(a>=b)
    max0=a;
    else
    max0=b;
}
int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    Max(a,b);
    printf("%d",max0);
    return 0;;
}