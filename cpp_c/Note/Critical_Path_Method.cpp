#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;
/*
    拓补排序解决了节点先后
    关键路径解决最长路径or哪个任务是核心时间瓶颈
    顶点：表示“事件”。
    有向边：表示“活动”，边权表示该活动的持续时间。
    源点：工程的开始。
    汇点：工程的结束。
    关键值：
        事件最早发生时间ve[i]:vi最早发生时间，从源点开始，按拓补排序向后推
            公式：边i->j，ve[j]=max{ve[i]+w(i,j)},取决于最晚完成的那个边
        事件最迟发生时间vl[i]:类似上面 vl[j]=min{vl[i]-w[j,i]};
        活动最早开始时间e[k]:e[k]=ve[i];起点最早开始时间
        活动最迟开始时间：l[k]=vl[i]-w[k,i];
    关键活动判定：l[k]-e[k]=0;(没有等待时机)
*/         
struct Edge{
    int to;
    int weight;
};
void criticalPath(int n,vector<vector<Edge>> &adj)//adj[u]表示从u发出的边的数组
{
    /*拓补排序*/
    vector<int> inDgree(n,0);
    for (int i=0;i<n;i++)
    {
        for(Edge j:adj[i])
        {
            inDgree[j.to]++;//统计入度
        }
    }
    //拓补排序计算ve
    vector<int> ve(n,0);
    vector<int> topoOrder;//记录拓补排序的顺序
    queue<int> q;
    for(int i=0;i<n;i++)
    {
        if(inDgree[i]==0)
        q.push(i);
    }
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        topoOrder.push_back(u);
        for(Edge v:adj[u])
        {
            int vv=v.to;
            ve[vv]=max(ve[vv],ve[u]+v.weight);
            if(--inDgree[vv]==0)
            q.push(vv);
        }
    }
    if(topoOrder.size()!=n)
    return;
    //逆序拓补计算vl
    int maxtime=ve[topoOrder.back()];//到达终点的时间
    vector<int> vl(n,maxtime);
    for(int i=n-1;i>=0;i--)
    {
        int u=topoOrder[i];
        for(Edge e:adj[u])
        {
            int v=e.to;
            vl[u]=min(vl[u],vl[v]-e.weight);
        }
    }
    //计算关键路径
    for(int u=0;u<n;u++)
    {
        for(Edge e:adj[u])
        {
            int v=e.to;
            int ee=ve[u];
            int el=vl[v]-e.weight;
            if(ee=el)
            {
                cout << "活动 <" << u << ", " << v << "> , 耗时: " << e.weight 
                        << " [事件" << u << "最早:" << ve[u] << ", 事件" << v << "最迟:" << vl[v] << "]" << endl;
            }
        }
    }
    
}
int main()
{

}