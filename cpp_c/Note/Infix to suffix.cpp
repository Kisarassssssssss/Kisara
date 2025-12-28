#include <iostream>
#include <stack>
#include <string>

using namespace std;
#define MAX 10001

stack<char> s;
string infix;
char suffix[MAX];
int k = 0; // 将k设为全局或在transfer中维护并返回，用于记录后缀表达式长度

// 获取运算符优先级的辅助函数
int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void transfer()
{
    k = 0;
    for (int i = 0; i < infix.length(); i++)
    {
        // 1. 如果是数字/操作数，直接输出
        if (infix[i] >= '0' && infix[i] <= '9') // 注意：这里只处理了单字符数字，如果是字母变量也可加上
        {
            suffix[k++] = infix[i];
        }
        // 2. 左括号直接入栈
        else if (infix[i] == '(')
        {
            s.push('(');
        }
        // 3. 右括号，弹出直到遇到左括号
        else if (infix[i] == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                suffix[k++] = s.top();
                s.pop();
            }
            if (!s.empty()) s.pop(); // 弹出 '('
            else { cout << "error: mismatched ()" << endl; exit(-1); }
        }
        // 4. 运算符
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
        {
            // 当栈不为空，且栈顶不是左括号，且栈顶优先级 >= 当前优先级时
            // 需要弹出栈顶元素（保证左结合性）
            while (!s.empty() && s.top() != '(' && getPriority(s.top()) >= getPriority(infix[i]))
            {
                suffix[k++] = s.top();
                s.pop();
            }
            s.push(infix[i]);
        }
        else {
            // 处理非法字符
             cout << "error: invalid char" << endl; exit(-1);
        }
    }
    // 5. 将栈中剩余元素弹出
    while (!s.empty())
    {
        if(s.top() == '(') { cout << "error: mismatched ()" << endl; exit(-1); }
        suffix[k++] = s.top();
        s.pop();
    }
}

void printsuffix()
{
    // 修改点：只打印到 k，而不是 infix.length()
    for (int i = 0; i < k; i++)
    {
        cout << suffix[i];
    }
    cout << endl;
}

int main()
{
    cin >> infix;
    transfer();
    printsuffix();
    return 0;
}