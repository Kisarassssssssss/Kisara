#include <iostream>
#include <algorithm>
using namespace std;
#define MAXSIZE 10001
#define INF 0x3f3f3f3f
int dist[MAXSIZE][MAXSIZE];
/*
    灵魂拷问：为什么 k（中转点）必须在最外层？
    这是 Floyd 算法最容易写错的地方！如果你把 k放在内层，算法就废了。
    原理（动态规划思想）：
    Floyd 本质是动态规划。
    k在最外层表示：“我们现在已经考虑过了前 k个点作为中转站的所有可能性”。

*/
void floyd(int n)
{
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(dist[i][k]!=INF&&dist[k][j]!=INF)
                {
                    if(dist[i][j]>dist[i][k]+dist[k][j])
                    dist[i][j]=dist[i][k]+dist[k][j];//以k为中继节点
                }
            }
        }
    }
}
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i==j)
            dist[i][j]=0;
            else dist[i][j]=INF;
        }
    }
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        dist[u][v]=min(dist[u][v],w);//处理重边
    }
    floyd(n);
    return 0;
}