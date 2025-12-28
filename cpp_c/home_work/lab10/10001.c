#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node 
{
    char name[50];
    int level; 
    struct Node* next;
} Node;
typedef struct Queue 
{
    Node* front;
    Node* rear;
} Queue;
void initQueue(Queue* q) 
{
    q->front = NULL;
    q->rear = NULL;
}
Node* createNode(const char* name, int level) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;
    strncpy(newNode->name, name, 49);
    newNode->name[49] = '\0';
    newNode->level = level;
    newNode->next = NULL;
    return newNode;
}
void request(Queue* q, const char* name, int level) 
{
    Node* newNode = createNode(name, level);
    
    if (q->front == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    if (level > q->front->level) {
        newNode->next = q->front;
        q->front = newNode;
    } 
    else {
        Node* curr = q->front;
        while (curr->next != NULL && curr->next->level >= level) 
        {
            curr = curr->next;
        }
        
        newNode->next = curr->next;
        curr->next = newNode;
        if (newNode->next == NULL) 
        {
            q->rear = newNode;
        }
    }
}


void download(Queue* q) 
{
    if (q->front == NULL) {
        printf("队列为空，没有可下载的任务。\n");
        return;
    }
    Node* temp = q->front;
    printf("下载中：%s (level=%d)\n", temp->name, temp->level);
    
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL; 
    }
    
    free(temp);
}


void removeUser(Queue* q, const char* name) 
{
    if (q->front == NULL) {
        printf("队列为空，无法删除。\n");
        return;
    }
    Node* prev = NULL;
    Node* curr = q->front;
    while (curr != NULL && strcmp(curr->name, name) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) 
    {
        printf("未找到用户：%s\n", name);
        return;
    }
    if (curr == q->front && curr == q->rear)
    { 
        q->front = q->rear = NULL;
    } 
    else if (curr == q->front) 
    { 
        q->front = curr->next;
    } 
    else if (curr == q->rear) 
    { 
        q->rear = prev;
        prev->next = NULL;
    } else 
    { 
        prev->next = curr->next;
    }
    free(curr);
    printf("已删除用户：%s\n", name);
}


void display(Queue* q) 
{
    if (q->front == NULL)
    {
        printf("当前队列为空。\n");
        return;
    }
    Node* curr = q->front;
    printf("当前下载队列：\n");
    while (curr != NULL) 
    {
        printf("用户名: %-10s | level: %d\n", curr->name, curr->level);
        curr = curr->next;
    }
}

int main() 
{
    Queue q;
    initQueue(&q);
    char command[50];
    char name[50];
    int level;
    printf("=== 某度网盘下载调度系统 ===\n"); 
    printf("支持命令：Request 用户名 level | Download | Remove 用户名 | Display | Exit\n");
    printf("请输入命令：\n");
    while (1) 
    {
        if (scanf("%s", command) == EOF) break;

        if (strcmp(command, "Request") == 0) 
        {
            scanf("%s %d", name, &level);
            if (level < 1 || level > 3) 
            {
                printf("无效的用户等级，请输入 1（普通） 2（VIP） 3（SVIP）。\n");
            } 
            else 
            {
                request(&q, name, level);
                printf("用户 %s (level=%d) 已加入队列。\n", name, level);
            }
        } 
        else if (strcmp(command, "Download") == 0) {
            download(&q);
        } 
        else if (strcmp(command, "Remove") == 0) {
            scanf("%s", name);
            removeUser(&q, name);
        } 
        else if (strcmp(command, "Display") == 0) {
            display(&q);
        } 
        else if (strcmp(command, "Exit") == 0) {
            printf("程序已退出。\n");
            break;
        } 
        else 
        {
            printf("无效命令，请重新输入。\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF); 
        }
    }

    return 0;
}