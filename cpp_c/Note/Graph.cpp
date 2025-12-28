#include <iostream>
using namespace std;
#define MAXSIZE 100001
typedef char VertexType;
typedef int EdgeType;
/*
    图论：
    基本概念
    有向图
    G=<V,E>
    V={1,2,3}
    E={<1,2>,<2,1>,<2,3>}
    无向图
    belike有向，边<v,w>依附于顶点v，m
    简单图：无重复边，无指向自己的边
    多重图：简单图补集
    （简单）完全图：任意两个顶点之间都存在边
    子图：G=（V，E）和G0=(V0,E0),(V0是V的子集，E0是E的子集)，则G0是G的子集，
    节点集合V相等的子集称为G的生成子集；
    在无向图中，如果从顶点 u 到顶点 v 存在一条路径（由边连接的一系列顶点），
    则称顶点 u 和 v 是连通的。
    对于无向图 G，如果图中任意两个不同的顶点都是连通的（即图中不存在“孤岛”部分），
    则称 G 为连通图。

    无向图中的极大连通子图称为连通分量
    定义：一个非连通图可以划分为若干个极大连通子图。这里的“极大”意味着：
    1.这个子图本身是连通的。
    2.你无法再从这个子图外（原图中剩余的部分）加入任何一个顶点还能保持子图连通。
    separate(极小连通子图，极大连通子图)，
    “极大”是对“外”的：在原图的范围内，看能否加入新顶点。
    “极小”是对“内”的：在子图本身的范围内，看能否删除已有边。

    有向图：
    在有向图中，若从顶点v vv到顶点w ww和从顶点w ww到项点v vv之间都有路径,
    则称这两个顶点是强连通的。若图中任何一对顶点都是强连通的，
    则称此图为强连通图。有向图中的极大强连通子图称为有向图的强连通分量。
    PS：:强连通图、强连通分量只是针对有向图而言的。
    一般在无向图中讨论连通性，在有向图中考虑强连通性

    连通图的生成树是包含图中全部顶点的一个极小连通子图。
    若图中顶点数为n nn,则它的生成树含有n−1条边。
    对生成树而言，若砍去它的一条边，则会变成非连通图，
    若加上一条边则会形成一个回路。在非连通图中，
    连通分量的生成树构成了非连通图的生成森林。
    度      无向图	与该顶点相连的边的数量	deg(v) 或 d(v)	这个点有多少条“连线”
    入度	有向图	指向该顶点的边的数量	deg⁺(v) 或 in(v)	有多少条边“进入”这个点
    出度	有向图	从该顶点指出的边的数量	deg⁻(v) 或 out(v)	有多少条边“离开”这个点
    稀疏图：当V节点个数<V*logV;
    稠密图；
    路径：点集；路径长度：边数；回路：路径终点和起点相同；E>V-1,一定有环
    简单路径，简单回路：中间顶点不重复出现
    距离：最短路径长度，不存在则为无穷
    有向树：顶点入度为0,其余顶点入度为1的右向图

*/
    //图的存储结构：
/*
        邻接矩阵：
        1.一维顶点数组
        2.二维数组，a[i][j]=1,i->j存在,a[i][j]=0,i->j不存在
        无向图的邻接矩阵一定是一个实对称矩阵
        带权图将1改为权重存储
*/
typedef struct{
    VertexType Vex[MAXSIZE];
    EdgeType Edge[MAXSIZE][MAXSIZE];
    int vexnum,arcnum;
}MGraph;

/*
    邻接表，为每个节点依次创造一个单链表，依次指向自己能到达的地方
*/
typedef struct EdgeNode{
    int adjvex;  //指向顶点的下标或者位置
    EdgeType weight;
    struct EdgeNode * next;
}EdgeNode;//边表
typedef struct VertexNode1{
    VertexType data;
    EdgeNode *firtedge;
}VertexNode1;//顶点表节点

typedef struct{
    VertexNode1 adjlist[MAXSIZE];//所有边
    int numV,numE;//定点数，边数；
}List;//逆邻接表算入度方法类似
/*
    十字链表，结合邻接表和逆邻接表的十字链表
*/
/*
    邻接多重表 当我们做 DFS 遍历或者删除边时，因为内存中只有这唯一的一个边节点对象：
            标记方便：把 mark 设为 true，下次从另一头走到这里时，直接就能看到它已经被访问了。
            删除方便：修改指针即可，不需要去另一个链表里“大海捞针”找对应的边。
*/

typedef struct Ebox{
    int mark;
    int ivex,jvex;//连接的两个节点的下标
    struct Ebox *ilink;//指向下一个依附于iex的边
    struct Ebox *jlink;
    EdgeType weight;
}Ebox;//边
typedef struct VexNode2{
    VertexType data;
    Ebox *firstedge;//指向依附的第一条边
}VexNode2;
typedef struct{
    VexNode2 adjmulist[MAXSIZE];//节点的数组
    int numv,nume;
}AMLGraph;