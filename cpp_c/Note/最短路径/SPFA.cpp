/*
    核心思想：Gossip,消息扩散。来自于一个直觉：只有上一个点的最短路径变短了，他的邻居才可能变短
    和dijkstra的关键区别：变短了就再次入对，顺序进入，哪里有问题就补哪里，支持负数，但容易被卡住
    SPFA (FIFO Queue)：先来后到。它可能会先处理一个比较大的距离，导致后面产生大量的无效更新。
    Dijkstra (Priority Queue)：永远先处理最小的距离。这是一种**“最优性剪枝”**，
    它保证了每一条边被松弛时，其起点的距离已经是当前最优的，从而避免了重复工作。
    */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MAXSIZE 100001
#define INF 0x3f3f3f3f
struct Edge{
    int to,weight,next;
}edges[MAXSIZE];
int head[MAXSIZE],total=0;
void addedge(int u,int v,int w)
{
    edges[++total]={v,w,head[u]};
    head[u]=total;
}
int dist[MAXSIZE];
bool in_queue[MAXSIZE];//现在是否在队列
int cnt[MAXSIZE];//记录每个点的入队次数
bool spfa(int starpoint,int n)
{
    for(int i=1;i<=n;i++)
    {
        dist[i]=INF;
        in_queue[i]=false;
        cnt[i]=0;
    }
    queue<int> q;
    q.push(starpoint);
    in_queue[starpoint]=true;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        in_queue[u]=false;
        for(int i=head[u];i;i=edges[i].next)
        {
            int v=edges[i].to;
            int w=edges[i].next;

            if(dist[u]+w<dist[v])
            {
                dist[v]=dist[u]+w;
                if(!in_queue[v])
                {//如果当前没有入队，入队更新邻居
                    q.push(v);
                    in_queue[v]=true;
                    cnt[v]++;
                    /*如果图中有一个圈，圈上所有边的和是负数，那么你可以绕着这个圈无限跑。
                    */
                    if(cnt[v]>=n)
                    return false;
                }
            }
        }
    }
    return true;
}