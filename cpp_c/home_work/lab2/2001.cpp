#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================== 公共类型 & 宏 ================== */

typedef struct {
    long long compares;
    long long moves;
} Metrics;

#define INTEREST_NOT_FOUND (-1.0f)

typedef struct {
    int id;             
    float interest;     
} Customer;

/* ================== 参数区 ================== */
#ifndef N_BENCH
#define N_BENCH 20000          
#endif
#define CAPACITY (N_BENCH + 1024)

/* =============== 工具 & 打印 =============== */
static void print_head_no_count(const char *title, const Customer *arr, int n) {
    printf("---- %s ----\n", title);
    for (int i = 0; i < n; ++i) {
        printf("[%05d] id=%d interest=%.2f\n", i, arr[i].id, arr[i].interest);
    }
}

/* ================= 无序数组 ================= */

/* 线性查找 */
float uaFindInterestById(const Customer customers[], int n, int id, Metrics *m) {
    for(int i = 0; i < n; i++) {
        // 统计比较次数
        if(m) m->compares++;
        
        if(customers[i].id == id) {
            return customers[i].interest;
        }
    }
    return INTEREST_NOT_FOUND;
}

/* 尾部插入 */
int uaInsertBack(Customer customers[], int n, int capacity, Customer c, Metrics *m) {
    if(n == capacity) {
        return -1;
    }
    customers[n] = c;
    // 统计数据移动（赋值也算移动）
    if(m) m->moves++;
    
    return n + 1;
}

/* 按id删除 */
int uaDeleteById(Customer customers[], int n, int id, Metrics *m) {
    int idx = -1;
    // 1. 查找
    for(int i = 0; i < n; i++) {
        if(m) m->compares++; // 统计比较
        if(customers[i].id == id) {
            idx = i;
            break;
        }
    }

    // 2. 检查是否找到 (必须在移动之前检查)
    if(idx == -1) {
        return -1;
    }

    // 3. 移动删除
    for(int i = idx + 1; i < n; i++) {
        customers[i-1] = customers[i];
        if(m) m->moves++; // 统计移动
    }
    
    return n - 1;
}


/* ================= 有序数组（按id升序） ================= */

/* 二分查找 */
float oaFindInterestById(const Customer customers[], int n, int id, Metrics *m) {
    int lo = 0, hi = n - 1;
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        
        // 统计比较
        if(m) m->compares++;
        
        if(customers[mid].id == id) {
            return customers[mid].interest;
        }
        else if(customers[mid].id < id) {
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }
    return INTEREST_NOT_FOUND;
}

/* 保序插入 */
int oaInsertKeepOrder(Customer customers[], int n, int capacity, Customer c, Metrics *m) {
    if(n == capacity) {
        return -1;
    }
    
    // 寻找插入位置（寻找第一个 >= c.id 的位置）
    int lo = 0, hi = n;
    while(lo < hi) {
        int mid = (lo + hi) / 2;
        
        if(m) m->compares++; // 统计比较
        
        if(customers[mid].id >= c.id) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    int pos = lo;

    // 移动元素腾出位置
    for(int i = n; i > pos; i--) {
        customers[i] = customers[i-1];
        if(m) m->moves++; // 统计移动
    }

    // 插入新元素
    customers[pos] = c;
    if(m) m->moves++; // 统计移动

    return n + 1;
}

/* 按id删除 */
int oaDeleteById(Customer customers[], int n, int id, Metrics *m) {
    int lo = 0, hi = n - 1;
    int idx = -1;
    
    // 二分查找目标位置
    // 注意：这里必须是 lo <= hi，否则如果元素在最后一个位置(lo==hi)，循环不会执行
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        
        if(m) m->compares++; // 统计比较
        
        if(customers[mid].id == id) {
            idx = mid;
            break;
        }
        else if(customers[mid].id < id) {
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }

    // 如果没找到
    if(idx == -1) {
        return -1;
    }

    // 移动覆盖
    for(int i = idx + 1; i < n; i++) {
        customers[i-1] = customers[i];
        if(m) m->moves++; // 统计移动
    }

    return n - 1;
}

/* ================== 主程序：命令驱动 ================== */
int main(void) {
    static Customer ua[CAPACITY];
    static Customer oa[CAPACITY];
    int ua_n = 0;
    int oa_n = 0;
    char cmd[32];

    while (scanf("%31s", cmd) == 1) {
        if (strcmp(cmd, "UA_INSERT") == 0) {
            int id; float interest;
            if (scanf("%d %f", &id, &interest) != 2) return 0;
            Customer c = { id, interest };
            int new_n = uaInsertBack(ua, ua_n, CAPACITY, c, NULL);
            if (new_n == -1) printf("UA_INSERT FAIL\n");
            else { ua_n = new_n; printf("UA_INSERT OK %d\n", ua_n); }
        }
        else if (strcmp(cmd, "UA_FIND") == 0) {
            int id;
            if (scanf("%d", &id) != 1) return 0;
            float v = uaFindInterestById(ua, ua_n, id, NULL);
            if (v == INTEREST_NOT_FOUND) printf("UA_FIND NOT_FOUND\n");
            else printf("UA_FIND FOUND %.2f\n", v);
        }
        else if (strcmp(cmd, "UA_DELETE") == 0) {
            int id;
            if (scanf("%d", &id) != 1) return 0;
            int new_n = uaDeleteById(ua, ua_n, id, NULL);
            if (new_n == -1) printf("UA_DELETE NOT_FOUND\n");
            else { ua_n = new_n; printf("UA_DELETE OK %d\n", ua_n); }
        }
        else if (strcmp(cmd, "OA_INSERT") == 0) {
            int id; float interest;
            if (scanf("%d %f", &id, &interest) != 2) return 0;
            Customer c = { id, interest };
            int new_n = oaInsertKeepOrder(oa, oa_n, CAPACITY, c, NULL);
            if (new_n == -1) printf("OA_INSERT FAIL\n");
            else { oa_n = new_n; printf("OA_INSERT OK %d\n", oa_n); }
        }
        else if (strcmp(cmd, "OA_FIND") == 0) {
            int id;
            if (scanf("%d", &id) != 1) return 0;
            float v = oaFindInterestById(oa, oa_n, id, NULL);
            if (v == INTEREST_NOT_FOUND) printf("OA_FIND NOT_FOUND\n");
            else printf("OA_FIND FOUND %.2f\n", v);
        }
        else if (strcmp(cmd, "OA_DELETE") == 0) {
            int id;
            if (scanf("%d", &id) != 1) return 0;
            int new_n = oaDeleteById(oa, oa_n, id, NULL);
            if (new_n == -1) printf("OA_DELETE NOT_FOUND\n");
            else { oa_n = new_n; printf("OA_DELETE OK %d\n", oa_n); }
        }
        else if (strcmp(cmd, "PRINT_UA") == 0) {
            print_head_no_count("UNORDERED ARRAY", ua, ua_n);
        }
        else if (strcmp(cmd, "PRINT_OA") == 0) {
            print_head_no_count("ORDERED ARRAY", oa, oa_n);
        }
        else if (strcmp(cmd, "END") == 0) {
            break;
        }
        else {
            printf("UNKNOWN COMMAND: %s\n", cmd);
        }
    }
    return 0;
}