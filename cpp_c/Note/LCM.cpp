#include <stdio.h>
void RES(int a,int b)
{
    int i=(a<b)?a:b;
    while(i%a!=0||i%b!=0)
    i++;
    printf("%d",i);
}
int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    RES(a,b);
    return 0;
}