#include <stdio.h>
#include <string.h>
int num[1001];
char input[1001];
char a[10001];
char *s =a;
int i =0;
int record()
{
    memset(num,0,sizeof(num));
    memset(input,0,sizeof(input));
    while (*s >= '0' && *s <= '9') 
    {
        num[i]=num[i]*10 + (*s-'0');
        s++;
    }//解析数字
    while (*s != '=' && *s != '\0') 
    {
        if ((*s == '+' || *s == '-' || *s == '*' || *s == '/')) {
            input[i] = *s;
            s++;
        } else {
            printf("错误的运算符:%c",*s);
            return -1;
        }
        i++;
        while (*s >= '0' && *s <= '9') {
            num[i] = num[i] * 10 + (*s - '0');
            s++;
        }
    }//解析运算符
    return 1;
}
int main(void)
{
    scanf("%s",a);
    int flag=record();
    if(flag==-1)
    return 0;
    int sum = num[0];
    for (int j = 1; j <= i; j++) 
    {
        if (input[j-1] == '+') {
            sum += num[j];
        } else if (input[j-1] == '-') {
            sum -= num[j];
        } else if (input[j-1] == '*') {
            sum *= num[j];
        } else if (input[j-1] == '/') {
            
            sum /= num[j];
        } 
    }
    printf("%d", sum);
    return 0;
}