#include <iostream>
#include <vector>
using namespace std;

// 【数据结构定义】
// 十字链表的节点结构：包含行号、列号、数值、向下指针、向右指针
typedef struct OLNode{
    int row, col;
    int val;
    struct OLNode * nextrow; // 指向该行的右边下一个元素
    struct OLNode * nextcol; // 指向该列的下边下一个元素
    // 节点的构造函数
    OLNode(int r, int c, int v) : row(r), col(c), val(v), nextrow(NULL), nextcol(NULL) {};
} OLNode;

// 行头结点结构：存储行号和指向该行第一个节点的指针
typedef struct Rvector{
    int index;
    OLNode* fir;
} Rvector;

// 列头结点结构：存储列号和指向该列第一个节点的指针
typedef struct Cvector{
    int index;
    OLNode* fir;
} Cvector;

class CrossList{
private:
    int rows; // 总行数
    int cols; // 总列数
    int NZC;  // 非零元素个数 (Non-Zero Count)
    vector<Rvector> RHeads; // 存储所有行头结点的数组
    vector<Cvector> CHeads; // 存储所有列头结点的数组

public:
    // ==========================================，，，
    // 1. 普通构造函数（构造函数不需要返回值）
    // ==========================================
    CrossList(int r, int c) : rows(r), cols(c), NZC(0) {
        // 初始化头结点数组的大小
        RHeads.resize(rows);
        CHeads.resize(cols);
        // 初始化每一个头结点，将指针置空
        for(int i = 0; i < rows; i++){
            RHeads[i].index = i;
            RHeads[i].fir = NULL;
        }
        for(int i = 0; i < cols; i++){
            CHeads[i].index = i;
            CHeads[i].fir = NULL;
        }
    }

    // ==========================================
    // 2. 拷贝构造函数 (Deep Copy)
    // 触发场景：CrossList B = A; 或 CrossList B(A); 或 函数传参/返回对象时
    // ==========================================
    CrossList(const CrossList& others) : rows(others.rows), cols(others.cols), NZC(0) 
    {
        // 第一步：搭建骨架（分配内存空间，但不填数据）
        RHeads.resize(rows);
        CHeads.resize(cols);
        for(int i = 0; i < rows; i++){
            RHeads[i].index = i;
            RHeads[i].fir = NULL;
        }
        for(int i = 0; i < cols; i++){
            CHeads[i].index = i;
            CHeads[i].fir = NULL;
        }
        
        // 第二步：深拷贝数据
        // 必须遍历源对象(others)的节点，手动取出数值，插入到当前对象(this)的新内存中
        // 绝对不能直接复制指针地址 (p = others.p)，否则会导致 Double Free 错误
        for(int i = 0; i < rows; i++){
            OLNode* p = others.RHeads[i].fir;
            while(p){
                // 调用 Insert，其内部会执行 new OLNode，从而申请新的独立内存
                Insert(p->row, p->col, p->val);
                p = p->nextrow;
            }
        }
    }

    // ==========================================
    // 3. 析构函数
    // 作用：对象销毁时自动调用，释放堆内存，防止内存泄漏
    // ==========================================
    ~CrossList()
    {
        for(int i = 0; i < rows; i++){
            OLNode* p = RHeads[i].fir;
            while(p){
                OLNode* q = p->nextrow; // 先保存下一个节点的地址
                delete p;               // 只有 new 出来的东西才需要 delete
                p = q;                  // 继续处理下一个
            }
        }
    }

    // ==========================================
    // 4. 赋值运算符重载 (Deep Copy)
    // 触发场景：对象已存在，进行赋值。如 A = B;
    // ==========================================
    CrossList& operator=(const CrossList& others) {
        // Step 1: 防止自赋值 (A = A)，否则先删除自己数据后就无法复制了
        if (this == &others) return *this; 

        // Step 2: 清理旧资源 (析构函数的逻辑)
        // 必须先清空当前对象已有的节点，防止内存泄漏
        for(int i = 0; i < rows; i++){
            OLNode* p = RHeads[i].fir;
            while(p){
                OLNode* q = p->nextrow;
                delete p;
                p = q;
            }
        }
        RHeads.clear(); // 清空 vector 内容
        CHeads.clear();

        // Step 3: 复制基础属性
        rows = others.rows;
        cols = others.cols;
        NZC = 0;

        // Step 4: 重新分配骨架
        RHeads.resize(rows);
        CHeads.resize(cols);
        for(int i = 0; i < rows; i++) { RHeads[i].index = i; RHeads[i].fir = NULL; }
        for(int i = 0; i < cols; i++) { CHeads[i].index = i; CHeads[i].fir = NULL; }

        // Step 5: 复制数据 (逻辑同拷贝构造)
        for(int i = 0; i < rows; i++){
            OLNode* p = others.RHeads[i].fir;
            while(p){
                Insert(p->row, p->col, p->val);
                p = p->nextrow;
            }
        }
        return *this; // 返回当前对象的引用，支持链式赋值 (A = B = C)
    }

    // ==========================================
    // 5. 插入函数 (核心逻辑)
    // ==========================================
    void Insert(int r, int c, int val){
        if(r < 0 || r >= rows || c < 0 || c >= cols){
            cout << "插入位置错误！" << endl;
            return;
        }
        
        // 申请新节点内存
        OLNode* newNode = new OLNode{r, c, val};

        // --- 处理行链表 (插入排序逻辑) ---
        // 如果行头为空，或者新节点列号比第一个节点还小 -> 插在头部
        if(!RHeads[r].fir || RHeads[r].fir->col > c)
        {
            newNode->nextrow = RHeads[r].fir;//如果行头为空，相当于指向 NULL
            RHeads[r].fir = newNode;
        }
        else // 否则，在链表中寻找合适的位置插入
        {
            OLNode* p = RHeads[r].fir;
            // 找到最后一个列号小于 c 的节点
            while(p->nextrow && p->nextrow->col < c){
                p = p->nextrow;
            }
            // 此时 p 在新节点的前面
            newNode->nextrow = p->nextrow;
            p->nextrow = newNode;
        }

        // --- 处理列链表 (逻辑同上) ---
        if(!CHeads[c].fir || CHeads[c].fir->row > r)
        {
            newNode->nextcol = CHeads[c].fir;
            CHeads[c].fir = newNode;
        }else
        {
            OLNode* p = CHeads[c].fir;
            while(p->nextcol && p->nextcol->row < r){
                p = p->nextcol;
            }
            newNode->nextcol = p->nextcol;
            p->nextcol = newNode;
        }
        NZC++;
    }

    // 删除非零元素
    void remove(int r, int c){
        if(r < 0 || r >= rows || c < 0 || c >= cols) return;
        
        // --- 从行链表中摘除 ---
        OLNode* p = RHeads[r].fir;
        OLNode* pre = NULL;
        while(p && p->col != c){ // 寻找目标节点
            pre = p;
            p = p->nextrow;
        }
        if(!p) return; // 没找到

        if(!pre){ // 如果是行头
            RHeads[r].fir = p->nextrow;
        }else{
            pre->nextrow = p->nextrow;
        }

        // --- 从列链表中摘除 ---
        // 注意：这里不用 delete p，因为节点是同一个内存，等把行和列都断开后，最后统一 delete
        OLNode* p_col = CHeads[c].fir; // 为了安全，这里重新遍历找指针
        pre = NULL;
        while(p_col && p_col->row != r){
            pre = p_col;
            p_col = p_col->nextcol;
        }
        if(!pre){
            CHeads[c].fir = p_col->nextcol;
        }else{
            pre->nextcol = p_col->nextcol;
        }

        delete p; // 真正释放内存
        NZC--;
    }

    // 查找特定位置的值 (const 保证不修改对象)
    int getValue(int r, int c) const {
        if(r < 0 || r >= rows || c < 0 || c >= cols) return 0;
        OLNode* p = RHeads[r].fir;
        while(p){
            if(p->col == c) return p->val;
            p = p->nextrow;
        }
        return 0; // 没找到节点，说明是稀疏部分的 0
    }

    void printMatrix(){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                cout << getValue(i, j) << "\t";
            }
            cout << endl;
        }
    }

    // 转置矩阵
    CrossList Transpose()
    {
        CrossList temp(cols, rows); // 创建行变列的新矩阵
        for(int i = 0; i < rows; i++)
        {
            OLNode* p = RHeads[i].fir;
            while(p)
            {
                // 原来的 (i, j, val) 变成 (j, i, val)
                temp.Insert(p->col, p->row, p->val);
                p = p->nextrow;
            }
        }
        return temp; // 返回新对象 (可能触发 RVO 优化或移动构造)
    }

    // ==========================================
    // 6. 加法运算符重载
    // 语法：CrossList C = A + B;
    // ==========================================
    CrossList operator+(const CrossList& other) const
    {
        CrossList result(rows, cols); // 创建结果对象
        // 遍历整个矩阵 (注意：这种双重循环方式对于非常稀疏的矩阵效率较低，是O(rows*cols))
        // 优化的稀疏加法应该只遍历两个矩阵的非零节点链表进行归并
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                // 计算和
                int sum = getValue(i, j) + other.getValue(i, j);
                // 优化：只有和不为0时才插入
                if (sum != 0) { 
                    result.Insert(i, j, sum);
                }
            }
        }
        return result; // 返回临时对象，会调用拷贝构造函数(或移动构造)赋值给外部变量
    }
};

int main()
{
    CrossList ls1(3, 2);
    ls1.Insert(0, 0, 1);
    ls1.Insert(0, 1, 2);
    ls1.Insert(1, 0, 3);
    ls1.Insert(1, 1, 4);
    ls1.Insert(2, 0, 5);
    ls1.Insert(2, 1, 6);

    cout << "Matrix ls1:" << endl;
    ls1.printMatrix();
    cout << endl;

    // 触发拷贝构造函数 (Initialization)
    CrossList ls2 = ls1; 
    
    // 触发 operator+，返回临时对象，然后触发拷贝构造(或优化)给 ls3
    CrossList ls3 = ls1 + ls2; 
    
    cout << "Matrix ls3 (ls1 + ls2):" << endl;
    ls3.printMatrix();

    return 0;
}
/*

*/