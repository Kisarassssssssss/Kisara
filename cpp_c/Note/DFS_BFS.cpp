#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAXSIZE 100001

typedef struct ENode{
    int adjvex;
    struct ENode *next;
}ENode;//边

typedef struct VertexNode{
    char data;
    ENode * firstedge;
}VertexNode;//节点

typedef struct{
    VertexNode adjlist[MAXSIZE];
    int numv,nume;
}Graph;

bool visited[MAXSIZE]={false};//每个节点是否访问

//=====================================
//深度优先搜索DFS
//=====================================
void DFS(Graph g,int i)//对下标为i的节点访问
{
    ENode *p;
    visited[i]=true;
    cout<<g.adjlist[i].data<<" ";
    p=g.adjlist[i].firstedge;
    while(p!=nullptr)//访问所有的边
    {
        if(!visited[p->adjvex])
        {
            DFS(g,p->adjvex);
        }
        p=p->next;
    }
}

void DFSstart(Graph g)
{
    for(int i=0;i<g.numv;i++)
    {
        if(!visited[i])
        {
            DFS(g,i);//保证对森林的检索
        }
    }
    cout<<endl;
}
// ==========================================
// 2. 广度优先搜索 (BFS) 
// ==========================================
void BFS(Graph g)
{
    ENode *p;
    queue<int> q;
    for(int i=0;i<g.numv;i++)
    visited[i]=false;

    for(int i=0;i<g.numv;i++)
    {
        if(!visited[i])//外层循环处理非连通图
        {

            //访问起始节点
            visited[i]=true;
            cout<<g.adjlist[i].data<<" ";
            q.push(i);//先入队先访问对应的下一个节点
            while(!q.empty())
            {
                int u=q.front();
                q.pop();
                p=g.adjlist[u].firstedge;//先访问u的下一层
                while(p!=nullptr)
                {
                    if(!visited[p->adjvex])
                    {
                        visited[p->adjvex]=true;
                        cout<<g.adjlist[p->adjvex].data<<" ";
                        q.push(p->adjvex);
                    }
                    p=p->next;
                }
            }
        }
    }
    cout<<endl;
}
/*
    连通性：
    图的遍历算法可以用来判断图的连通性。 
    对于无向图来说，若无向图是连通的，则从任一结点出发， 仅需一次遍历就能够访问图中的所有顶点；若无向图是非连通的，
    则从某一个顶点出发，一次遍历只能访问到该顶点所在连通分量的所有顶点，而对于图中其他连通分量的顶点，则无法通过这次遍历访问。
    对于有向图来说，若从初始点到图中的每个顶点都有路径，则能够访问到图中的所有顶点，否则不能访问到所有顶点。
*/