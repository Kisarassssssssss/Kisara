#include <iostream>
#include <algorithm>
using namespace std;
#define MAXSIZE 1000001
/*
    MST最小生成树
    输入一个无向图，去掉一些边，生成一颗树（无环，连通），并且生成树的总权重最小
*/
/*
    type1:Kruskal(基于边的贪心）：
        将所有边从小到大排序，每次寻找边，看两个端点是否连通，如果连通，就不再选取（否则成环）
        巧妙之处：通过parent数组，存储每一个节点的根节点，判断两个节点是否连通
        */
typedef struct{
    int v,u;
    int weight;
}Edge;
bool compareEdges(Edge a,Edge b)//升序排序
{
    return a.weight<b.weight;
}
int parent[MAXSIZE];//记录节点i的父亲
void initDSU(int n)
{
    for(int i=0;i<=n;i++)
    {
        parent[i]=i;
    }
}
int findroot(int i)//寻找根节点
                   //路径压缩，动态维护parent数组，更新完一次下一次更新会把历史记录归并
{
    if(parent[i]==i) return i;
    return parent[i]=findroot(parent[i]);
}
void Kruskal(int v,int e,Edge edges[])//顶点个数，边的个数
{
    sort(edges,edges+e,compareEdges);
    initDSU(v);
    int mst_weight=0;//权重之和
    int edges_count=0;//当前选择的边的条数
    for(int i=0;i<e;i++)
    {
        int rootu=findroot(edges[i].u);
        int rootv=findroot(edges[i].v);
        if(rootu!=rootv)//如果根节点不一样，说明他们不连通，需要选取这条边
        {
            parent[rootu]=rootv;//把u归入v的树
            mst_weight+=edges[i].weight;
            edges_count++;
        }
        if(edges_count==e-1)
        break;
    }

}