#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
struct  Node
{
    int data;
    int weight;//权重
    Node *l,*r;
    Node(int d,int w):data(d),weight(w),l(nullptr),r(nullptr){}
};
// 自定义比较器 (仿函数)
// 优先队列默认是大根堆，我们需要小根堆 (权重小的在上面)
// 在 priority_queue 中，返回 true 意味着 b 的优先级比 a 高 (b 排在 a 前面)
// 这里我们希望 weight 小的排在前面，所以当 l->weight > r->weight 时返回 true
struct Compare{
    bool operator()(Node *l,Node *r)
    {
        return l->weight>r->weight;
    }
};
int main()
{
    int n=6;
    int val[6]={2,1,4,3,6,5};
    int wt[6]={2,3,5,4,7};
    priority_queue<Node*,vector<Node*>,Compare> pq;//小堆优先队列,小元素优先出栈
    for(int i=0;i<n;i++)
    {
        pq.push(new Node(val[i],wt[i]));//创建森林
    }
    while(pq.size()>1)//如果还能合并
    {
        Node *l=pq.top();
        pq.pop();
        Node *r=pq.top();
        pq.pop();
        Node *parent=new Node(-1,l->weight+r->weight);//只有叶子节点存数据，-1为标识符，表示这不是叶子节点，不存储数据，只存储权重
        parent->l=l;
        parent->r=r;
        pq.push(parent);
    }
    Node *root=pq.top();
}