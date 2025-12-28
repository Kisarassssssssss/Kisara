#include <stdio.h>
#define MAX 201
int n,data[MAX];
int map[20][5]={0};
char sit[5]={'A','B','C','D','F'};
void jugde(int order)
{
    int flag=0;
    int left[20]={0};
    for(int i=0;i<20;i++)
    {
        int count=0;
        int flag=-1;//i行是否有空闲的标识
        for(int j=0;j<5;j++)
        {
            if (map[i][j]==0)
            count++;
            if(count>=data[order])
            {
                flag=1;
                flag=j;
                break;
            }
        }
        if(flag!=-1)
        {
            for(int j=flag-data[order]+1;j<=flag;j++)
            {
        map[i][j]=1;
        printf("%d%c",i+1,sit[j]);
        if(j!=flag) printf(" ");  
            }
            printf("\n");
            break;
        }
        left[i]=count;

    }
    if(flag==1)
    return;
    else
    {
        int cnt=0;
        for(int j=0;j<20;j++)
        {
            for(int k=0;k<5;k++)
            {
                if(map[j][k]==0)
                {
                    map[j][k]=1;
                    cnt++;
                    printf("%d%c",j+1,sit[k]);
                    if(cnt!=data[order]) printf(" ");
                    if(cnt==data[order])
                    {
                        printf("\n");
                        break;
                    }
                }
            }
            if(cnt==data[order])
            {
                break;
            }
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&data[i]);
    }
    for(int i=0;i<n;i++)
    {
        jugde(i);
    }
    return 0;
}