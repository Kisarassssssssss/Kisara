#include <stdio.h>
int main()
{
    char stack[1000001];
    int top=-1;
    char s[1000001];
    scanf("%s",s);
    char *p=s;
    while(*p!='\0')
    {
        if(*p=='{')
        {
            stack[++top]='{';
        }
        else if(*p=='[')
        {
            stack[++top]='[';
        }
        else if(*p=='}')
        {
            if(top==-1)
            {
                printf("0");
                return 0;
            }
            else if(stack[top]=='{')
            {
                top--;
            }
            else if(stack[top]=='[')
            {
                printf("0");
                return 0;
            }
        }
        else if(*p==']')
        {
            if(top==-1)
            {
                printf("0");
                return 0;
            }
            else if(stack[top]=='[')
            {
                top--;
            }
            else if(stack[top]=='{')
            {
                printf("0");
                return 0;
            }
        }
        p++;
    }
    if(top==-1)
    printf("1");
    else
    printf("0");
    return 0;
    
}