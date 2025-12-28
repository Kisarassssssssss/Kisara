#include <stdio.h>
int isLeapYear(int year)
{
    return (year%4==0&&year%100!=0)||(year%400==0);
}
int isValidDate(int y, int m, int d) 
{
    if(y<1990||m<1||m>12||d<1) 
        return 0;
    int daysInMonth[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(isLeapYear(y)) 
        daysInMonth[1]=29;
    return d<=daysInMonth[m-1];
}
int getTotalDays(int y, int m, int d) 
{
    int sum=0;
    for(int i=1990;i<y;i++) 
    {
        sum+=isLeapYear(i)?366:365;
    }
    int daysInMonth[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(isLeapYear(y)) 
        daysInMonth[1]=29;
    for(int i=0;i<m-1;i++) 
    {
        sum+=daysInMonth[i];
    }
    sum+=d;
    return sum;
}

int main() {
    int y,m,d;
    if(scanf("%4d-%2d-%2d",&y,&m,&d)!=3||!isValidDate(y,m,d)) 
    {
        printf("Invalid input");
        return 0;
    }
    int totalDays=getTotalDays(y,m,d);
    int result=totalDays%5;
    if(result>=1&&result<=3) 
    {
        printf("working");
    } 
    else 
    {
        printf("rest");
    }
    return 0;
}