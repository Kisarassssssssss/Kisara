#include <stdio.h>
int n;
void cs(int n,char s,char t,char r)
{
    if(n==1)
    {
        printf("Move disk from %c to %c\n",s,t);
        return;
    }
    cs(n-1,s,r,t);
    printf("Move disk from %c to %c\n",s,t);
    cs(n-1,r,t,s);
}
int main()
{
    scanf("%d",&n);
    cs(n,'A','C','B');
}
