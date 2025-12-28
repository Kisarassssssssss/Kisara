#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char s1[501],s2[501];
int result[501];
int max(int a,int b)
{
    return a>b?a:b;
}
void plus(char *s1,char *s2)
{
    int len1=strlen(s1);
    int len2=strlen(s2);
    int len=max(len1,len2);
    int *s3=(int *)malloc(sizeof(int)*(len+1)),
    *s4=(int *)malloc(sizeof(int)*(len+1));
    memset(s4,0,(len+1)*sizeof(int));
    memset(s3,0,(len+1)*sizeof(int));
    for(int i=0;i<len1;i++)
    {
        s3[i]=s1[len1-i-1]-'0';
    }
    for(int i=0;i<len2;i++)
    {
        s4[i]=s2[len2-i-1]-'0';
    }
    int pre=0;
    for(int i=0;i<max(len1,len2);i++)
    {
        int temp=s3[i]+s4[i]+pre;
        if(temp<10)
        {
            result[i]=temp;
            pre=0;
        }
        else{
            result[i]=temp-10;
            pre=1;
        }
    }
    if(pre==1)
    result[max(len1,len2)]=1,len++;
    for(int i=0;i<len;i++)
    {
        printf("%d",result[len-i-1]);
    }
    free(s3);
    free(s4);

}
int main()
{
    scanf("%s",s1);
    scanf("%s",s2);
    plus(s1,s2);
    return 0;
}