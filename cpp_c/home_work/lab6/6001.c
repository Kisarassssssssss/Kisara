#include <stdio.h>
int n,m;
typedef struct{
    int val[21];
    int max,min;
    int sum;
}stu;
int max(int a,int b)
{
    return a>b?a:b;
}
int min(int a,int b)
{
    return a<b?a:b;
}
double res[21]={0};
stu STU[101];
int main()
{
    scanf("%d %d",&n,&m);
    double MAX=0;
    for(int i=0;i<n;i++)
    {
        STU->max=0;
        STU->min=10;
        STU->sum=0;
        for(int j=0;j<m;j++)
        {
            scanf("%d",&STU[i].val[j]);
            STU[i].sum+=STU[i].val[j];
            STU[i].max=max(STU[i].max,STU[i].val[j]);
            STU[i].min=min(STU[i].min,STU[i].val[j]);
        }
        res[i]=(1.0*STU[i].sum-STU[i].max-STU[i].min)/(m-2.0);
        MAX=max(MAX,res[i]);
    }
    printf("%.2f",MAX);
    return 0;
}