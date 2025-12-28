#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXSIZE 1000001

typedef struct{
    int to;
    int weight;
    int next;//同一个顶点下一次指向的边
}EDGE;//链式前向型
EDGE edges[MAXSIZE];
int total=0;
int head[MAXSIZE];//u节点的第一条边
void addedge(int u,int v,int w)//起点->终点
{
    edges[++total]={v,w,head[u]};
    head[u]=total;
}
int dist[MAXSIZE];//从起点到u节点的总距离
bool visited[MAXSIZE];
typedef pair<int,int> PII;//二元向量,距离,节点标号
void dijkstra(int startpoint,int n)
{
    /*初始化*/
    for(int i=1;i<=n;i++)
    {
        dist[i]=INF;
        visited[i]=false;
    }
    priority_queue<PII,vector<PII>,greater<PII>> pq;//小堆优先队列
    dist[startpoint]=0;//起点到自己的距离是零
    pq.push({0,startpoint});
    while(pq.empty())
    {
        PII top=pq.top();
        pq.pop();
        int d=top.first;
        int u=top.second;
        if(!visited[u])
        continue;//如果当前最小的已经入对，就跳过
        visited[u]=true;
        for(int j=head[u];j;j=edges[j].next)
        {
            int v=edges[j].to;
            int w=edges[j].weight;
            if(dist[u]+w<dist[v])//起点到v的距离更新
            {
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});//推入待更新队列
            }
        }
    }
}
/*
    每次选一个最短的路径拉进来，并且更新待选队列，方便下一次选
*/
int main()
{

}