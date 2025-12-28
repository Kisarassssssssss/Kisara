#include <cstdlib>
#include <iostream>
using namespace std;
int main(void)
{
    int ival=1024;
    int &refVal=ival;//是引用，不是取地址
    // int &reval2;//引用必须初始化
    //引用后两个变量 会绑定在一起
    //引用并非对象，只是给一个已经存在的对象取得别名
    cout<<refVal<<" "<<ival<<endl;
    refVal=932;
    cout<<refVal<<" "<<ival<<endl;
    const int ci=1;
    const int &r2=ci;//合法，常量的引用指向常量
    //int &r3=ci;//非法，变量不能引用常量
    int i=4;
    const int &r4=i;//合法，常量引用非常量，绑定后i也是常量；
    i=9;
    cout<<r4<<endl;
    //const引用可以绑定到临时对象（一个数，a*2是一个表达值），非const只能绑定某一对象（a,b,c），不能绑定到临时值
    int *p1=nullptr,*p2=0,*p3=NULL;//空指针
    const int *a=&ci;//常量指针要和常量绑定
    int *const mun=&i;//指针指向的地址不变
    //int *const ii;//非法，常量指针需要初始化，非常量指针不初始化可以，但是不安全，会成为野指针；
    /*
    int *const 顶层const，指针本身不可变；
    const int *底层const，指针指向的内容不可变  *左顶层，*右底层
    */
    constexpr int sw=10;//constexpr在编译时就知道，可以放在数组里面，比const更加严格
    constexpr int* dp=nullptr;  //constexpr必须编译时就要确定！
    //等价于顶层指针
    int *const doo=nullptr;
    return 0;
}