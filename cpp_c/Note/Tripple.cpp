#include <stdio.h>
#include <stdlib.h>

//稀疏矩阵:矩阵中的非零元素比较少

//三元组的结点定义
#define MAX_SIZE 100//表中非零元素个数的最大值

typedef int ElemType;

//三元组结点定义
typedef struct Triple
{
    //三元组中非零元素的行下标和列下标
    int row;
    int col;
    ElemType e;//非零元素对应的值
}Triple;

//三元组顺序表定义
typedef struct TSMatrix
{
    Triple data[MAX_SIZE+1];//多余的一个位置用于存放非零元的个数
    int m_row,m_col,m_num;//矩阵的行数、列数(固定)和非零元的个数
}TSMatrix;

void creatSMatrix(ElemType *mat,int row,int col)
{
    int i,j;
    printf("请按行依次输入这个矩阵的元素:\n");
    for(i=1;i<=row;i++){
        for(j=1;j<=col;j++){
            scanf("%d",(mat+(i-1)*col+j));
        }
    }
}

void printSMatrix(ElemType *mat,int row,int col)
{
    printf("原始矩阵为:\n");
    int i,j;
    for(i=1;i<=row;i++){
        for(j=1;j<=col;j++){
            printf("%d\t",*(mat+(i-1)*col+j));
        }
        printf("\n");
    }
    printf("----------------------------------\n");
}

//对三元组进行处理
void initTriple(TSMatrix *M,ElemType *mat,int row,int col)
{
    M->m_row=0;
    M->m_num=0;
    M->m_col=3;//三元组矩阵默认为三列
    int i,j;
    for(i=1;i<=row;i++){
        for(j=1;j<=col;j++){
            if(*(mat+(i-1)*col+j)!=0){
                //非零元数增加一个
                M->m_num++;
                M->m_row++;
                M->data[M->m_num].row=i;
                M->data[M->m_num].col=j;
                M->data[M->m_num].e=*(mat+(i-1)*col+j);
            }
        }
    }
    //第0号位置存放的是原始矩阵的行数和列数，以及非零元的个数
    M->data[0].row=row;
    M->data[0].col=col;
    M->data[0].e=M->m_num;
}


void printTriple(TSMatrix M)
{
    //打印三元组
    printf("三元组矩阵为:\n");
    printf("行\t列\t值\n");
    int i;
    for(i=0;i<=M.m_row;i++){
        printf("%d\t%d\t%d\n",M.data[i].row,M.data[i].col,M.data[i].e);
    }
    printf("----------------------------------\n");
}

//将三元组表还原为稀疏矩阵
void printSMatrix2(TSMatrix M)
{
    int i,j;
    int row=M.data[0].row;
    int col=M.data[0].col;
    ElemType mat2[row][col];
    //写法一（比较常规）
    //写法二(数组中的每个元素默认值都为0)
    for(i=1;i<=M.m_num;i++){
        mat2[M.data[i].row][M.data[i].col]=M.data[i].e;
    }
    printf("原始矩阵为:\n");
    for(i=1;i<=row;i++){
        for(j=1;j<=col;j++){
            printf("%d\t",mat2[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------\n");
}

//普通转置思路
//参数中M指原三元组表，值传递
//参数中T指转置后的三元组表，引用传递
void TransposeSMatrix(TSMatrix M,TSMatrix *T)
{
    int T_index;////用于遍历T的非0行，共遍历t_num次
    int M_col;//记录三元组表M的列的数值，应该从1递增
    int M_index;//用于遍历M的非0行，共遍历m_num次
    //先将M的一些初始信息赋值为T
    T->m_row=M.m_row;
    T->m_col=M.m_col;
    T->m_num=M.m_num;
    T->data[0].row=M.data[0].col;
    T->data[0].col=M.data[0].row;
    T->data[0].e=M.data[0].e;//这相当于处理完了三元组表的第0行
    if(T->m_num>0){
        T_index=1;
        for(M_col=1;M_col<=M.m_col;M_col++){
            //这里的M_index从1开始，是因为我们上面已经处理好的第0行
            for(M_index=1;M_index<=M.m_num;M_index++){
                if(M.data[M_index].col==M_col){
                    T->data[T_index].row=M.data[M_index].col;
                    T->data[T_index].col=M.data[M_index].row;
                    T->data[T_index].e=M.data[M_index].e;
                    T_index++;
                }
            }
        }
    }
}

//三元组表的快速转置
/*
思路:
    按列查找每一列中的首非零元以及非零元的个数，并使用两个数组存储起来
    有cpot[n]=cpot[n-1]+num[n-1]
    并规定cpot[1]=1
    注意：这里不考虑稀疏矩阵或是三元组表的0行0列
*/
void FastTransposeSMatrix(TSMatrix M,TSMatrix *T2)
{
    int T2_index;////用于遍历T的非0行，共遍历t_num次
    int M_col;//记录三元组表M的列的数值，应该从1递增
    int M_index;//用于遍历M的非0行，共遍历m_num次

    int num[MAX_SIZE];//用于记录M中每一列的非零元素
    int cpot[MAX_SIZE];//用于记录M中每一列的首非零元素应该在T中的index(从1开始)

    //首先，分别从表结构和非零元两个方面赋值T2
    T2->m_row=M.m_row;
    T2->m_col=M.m_col;
    T2->m_num=M.m_num;
    T2->data[0].row=M.data[0].col;
    T2->data[0].col=M.data[0].row;
    T2->data[0].e=M.data[0].e;

    if(T2->m_num>0){
        //将数组num中的每个元素置0，防止默认值
        for(M_col=1;M_col<=M.m_col;M_col++){
            num[M_col]=0;
        }
        //遍历稀疏矩阵每一列，统计非零元的数量
        for(M_index=1;M_index<=M.m_num;M_index++){
            num[M.data[M_index].col]++;
        }

        //由于转置后相当于按列展开
        //默认（稀疏矩阵从第1行第1列开始）
        cpot[1]=1;

        for(M_col=2;M_col<=M.m_col;M_col++){
            cpot[M_col]=cpot[M_col-1]+num[M_col-1];
        }
        //遍历M的每一行
        for(M_index=1;M_index<=M.m_num;M_index++){
            //取每一行的列下标
            M_col=M.data[M_index].col;
            //带入cpot[]数组中，找到在T中的下标
            //cpot中存有所有非零元的位置信息
            T2_index=cpot[M_col];
            //互换信息
            T2->data[T2_index].row=M.data[M_index].col;
            T2->data[T2_index].col=M.data[M_index].row;
            T2->data[T2_index].e=M.data[M_index].e;
            //这个值是根据列来自增的
            //即每一列中除了首非零元，还剩下几个非零元就加几次
            cpot[M_col]++;
        }
    }
}

int main()
{
    printf("初始化稀疏矩阵...\n");
    int row,col;
    printf("请输入矩阵的行数和列数(row,col):");
    scanf("%d,%d",&row,&col);
    printf("\n");
    ElemType mat[row][col];
    TSMatrix M;
    TSMatrix T;
    TSMatrix T2;

    //创建稀疏矩阵
    creatSMatrix(*mat,row,col);
    printf("----------------------------------\n");
    //打印稀疏矩阵
    printSMatrix(*mat,row,col);
    //将稀疏矩阵转为三元组
    initTriple(&M,*mat,row,col);
    //打印三元组
    printTriple(M);
    //将三元组还原，并打印
    printf("还原后的");

    printSMatrix2(M);

    //转置三元组

    /*方法一*/
    TransposeSMatrix(M,&T);
    printf("普通转置后的");
    printTriple(T);
    /*方法二*/
    FastTransposeSMatrix(M,&T2);
    printf("快速转置后的");
    printTriple(T2);
    printf("Hello world!\n");
    return 0;
}
