#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
/*
    保证有向无环图中，对于边(u,v),u永远排在v的前面
    统计入度’
    入度为0,入对‘
    取出一个节点u,加入结构序列
    遍历u节点v，v的入度减1(保证u在v的前面)
*/
vector<int> topologicalSort(int n,vector<vector<int>>& adj)//adj是邻接表，adj[i]存储从i节点出发所有的边到达的终点
{
    vector<int> inDgree(n,0);//长度为n，初始值为0；
    for(int u=0;u<n;u++)
    {
        for(int v:adj[u])
        {
            inDgree[v]++;
        }
    }
    queue<int> q;
    for(int i=0;i<n;i++)
    {
        if(inDgree[i]==0)
        {
            q.push(i);
        }
    }
    //初始化
    vector<int> result;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        result.push_back(u);
        for(int v:adj[u])
        {
            inDgree[v]--;
            if(inDgree[v]==0)
            q.push(v);
        }
    }
    if(result.size()!=n)
    {
        return {};//是环
    }
    return result;
}
/*
    
*/