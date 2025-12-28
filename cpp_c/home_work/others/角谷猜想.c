#include <stdio.h>
int n;
int step=0;
void compute(int n)
{
    if(n==1)
    return;
    step++;
    if(n%2==0)
    compute(n/2);
    else
    compute(n*3+1);
}
int main()
{
    scanf("%d",&n);
    compute(n);
    printf("%d",step);
}