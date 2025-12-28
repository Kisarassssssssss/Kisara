#include <stdio.h>
#include <string.h>
int locate(char *s,char *t)
{
    int i=0,j=0;
    while(i<strlen(s)&&j<strlen(t))
    {
        if(s[i]==t[j])
        {
            i++;
            j++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
    if(j==strlen(t))
    return i-j+1;
    else return -1;
}
int main()
{
    char strs[]="hello world";
    char str[]="world";
    int index=locate(strs,str);
    printf("%d",index);
    return 0;
}