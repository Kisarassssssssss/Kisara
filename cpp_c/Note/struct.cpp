#include <bits/stdc++.h>
#include <typeinfo.h>
using namespace std;
// typedef struct{
//     int ki,pi,di;
// }PID;
// PID build_PID(int a,int b,int c)
// {
//     PID P;
//     P.di=a;
//     P.ki=b;
//     P.pi=c;
//     return P;
// }
// struct oo{
//     int i;
//     PID BOY;
// }o;
// union u{
//     int i;
//     char a[4] ;

// }uu;

// union mix{
//     int i ;
//     float f;
// };
struct{
    int x,y;
}x;
struct{
    int x,y;
}y;
struct v{
    double r,i;
};
struct color {
int red;
int green=0;
int blue;
};
int main(void)
{
    // PID pid={0,0,0};
    // PID pid2=build_PID(2,2,2);
    // o={0,{0,0,0}};
    // o.BOY.ki=7;
    // uu.i=255;
    // for(int i=0;i<=3;i++)
    // {
    //     cout<<bitset<8>(int(uu.a[i]))<<" ";
    // }
    // cout<<endl;
    // mix mixed[20000];
    // enum {a=1,b=2,c=3,d=4} s;
    v a,b,c;
    a={1.0,2.0};
    b=a;
    c.r=a.r-b.i;
    // cout<<a;
    x={1,2};
    y={4,6};
    cout<<c.r;
    const color MAGENTA={.red=89,.blue=0};
    return 0;
}