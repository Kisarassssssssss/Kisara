#include <iostream>
#include <vector>
#include <queue>

using namespace std;
/*

    MST_Prime
    “全员备选”：你说“队列中所有可能的边”，这说明你意识到这不是一个点的选拔，而是整棵树所有触角的选拔。
    “信息更新”：你提到“发现新的最短距离立刻更新”，这对应了代码里的 dist[v] > w 覆盖操作。
    “端点父亲”：你提到“记录端点当前的父亲”，这说明你理解了如何通过 parent 数组把这棵树的“骨架”给存下来。

    需要先从原始数据用addegde更新edges和head
    为什么同一个邻居可能会在队列里出现多次？
    当你发现一个更短的距离并 pq.push 时，旧的那条比较长的边还在队列里呆着呢！
    比如：节点 5 原本通过 A 进城要 10 块（已入队），后来发现通过 B 进城只要 5 块（又入队了）。
    现在队列里有两个 5 号点：{10, 5} 和 {5, 5}。
    结果：因为我们是小根堆，{5, 5} 会先弹出来。你把它标记为 visited[5] = true。
    重点：等后来那个 {10, 5} 弹出来时，你的那句 if (visited[u]) continue; 就像一个安检口，直接把这个“过时的旧信息”拦住扔掉了。
    这就是为什么 Prim 算法即使不从队列里删除旧数据，依然能跑得飞快的原因。

    播种：选一个点作为种子，把它能连出去的触角都扔进“拍卖行（PQ）”。
    成交：从拍卖行选一个最便宜的成交，把新成交的点拉进城。
    刷新报价：新进城的点带入新触角。如果新触角比拍卖行里现有的同目的地的触角更便宜，就往拍卖行里扔一个“新低价特惠”。
    循环：永远买最便宜的，直到全城通电。

*/
#define MAXSIZE 100001
#define INF 0x3f3f3f3f

typedef struct{
    int to;//终点节点代号编码
    int weight;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
    int next;//同一起点指向的下一条边
}Edge;
Edge edges[MAXSIZE];
int head[MAXSIZE];//存储节点u第一条边的序号
int total=0;//当前已存储的边的条数
void addEdge(int u,int v,int w)
{
    total++;
    edges[total].to=v;
    edges[total].weight=w;//记录权重
    edges[total].next=head[u];//连成链
    head[u]=total;//记录当前第一条节点的序号
}

int dist[MAXSIZE];//存储dist[u]到边界NULL的最短距离
int parent[MAXSIZE];//存储u节点的根节点
bool visited[MAXSIZE];//标记节点是否在树内     
typedef pair<int,int> PII;//距离，节点编号 
void prim(int n)
{
    for(int i=0;i<=n;i++)
    {
        dist[i]=INF;//所有点距离无限远，都不在树内；
        visited[i]=false;
        parent[i]=-1;
    }
    priority_queue<PII,vector<PII>,greater<PII>> pq;
    dist[1]=0;//选取1号为起点，它到边界的距离为0
    pq.push({0,1});
    while(!pq.empty()){
        PII top=pq.top();//拿出一个距离边界最近的点
        pq.pop();
        int d=top.first;//距离
        int u=top.second;//编号
        if(visited[u])
        continue;
        visited[u]=true;
        for(int i=head[u];i;i=edges[i].next)//遍历每一个边d
        {
            int v=edges[i].to;//找到邻居
            int w=edges[i].weight;//记录权重
            if(!visited[v]&&dist[v]>w)//邻居没被访问过，并且邻居路径比当前小
            {
                dist[v]=w;
                parent[v]=u;
                pq.push({dist[v],v});//更新距离，记录父亲
            }
        }
    }
}