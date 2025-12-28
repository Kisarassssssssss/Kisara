#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#define MAXSIZE 50001
char s[MAXSIZE];
typedef struct node{
    char s[101];
    int index;
}node;
typedef struct list{
    node lt[10001];
    int num;
}list;//数据库
list LIST;
void compare(char *ss,list * LS)//对比数据库
{
    if(LS->num==0)
    {
        LS->num++;
        LS->lt[1].index=1;
        strcpy(LS->lt[1].s,ss);
    }
    else
    {
        int flag=0;
        for(int i=1;i<=LS->num;i++)
        {
            if(!strcmp(ss,LS->lt[i].s))
            flag=-1;
        }
        if(flag==-1)
        return;
        else
        {
            LS->lt[++LS->num].index=1;
            strcpy(LS->lt[LS->num].s,ss);
        }
    }
}
void scan(char *s)
{
    int len=strlen(s);
    for(int i=0;i<len;i++)
    {
        if((!isalpha(s[i-1])||i==0) &&isalpha(s[i]))
        {
            int j=i;
            char temp[101];
            while(isalpha(s[j]))
            {
                temp[j-i]=tolower(s[j]);
                j++;
            }
            temp[j-i]='\0';
            i=j-1;
            compare(temp,&LIST);
        }
    }
}
int main()
{
    fgets(s, MAXSIZE, stdin);
    LIST.num=0;
    scan(s);
    printf("%d",LIST.num);
}