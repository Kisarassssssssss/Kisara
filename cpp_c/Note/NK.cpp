#include  <stdio.h>
int NK(int n,int k)
{
    if(k>=2)
    return n*NK(n,k-1);
    else if(k==1)
    return n;
    if (k<1)
    return 0;
}
int main(void)
{
    int n,k;
    scanf("%d %d",&n,&k);
    printf("%d",NK(n,k));
    return  0;
}