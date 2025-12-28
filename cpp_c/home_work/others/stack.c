#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    char val;
    struct node *next;
}node;
typedef struct{
    int num;
    node* top;
}Stack;
void Push(Stack *s,char c)
{
    node *Newnode=(node*)malloc(sizeof(node));
    Newnode->val=c;
    Newnode->next=s->top;
    s->num++;
    s->top=Newnode;
}

void Initstack(Stack *stack){
    stack->num=0;
    stack->top=NULL;
}
void POP(Stack* s)
{
    s->num--;
    printf("%c",s->top->val);
    node *temp=s->top;
    s->top=s->top->next;
    free(temp);
}
void Print(Stack *s)
{
    while(s->num>0)
    {
        POP(s);
    }
}
int main()
{
    Stack stack;
    Initstack(&stack);
    char str[1001];
    fgets(str, sizeof(str), stdin);
    for (int i = 0; str[i] != '\0'; i++) 
    {
        if (str[i] != '\n') 
        {  
            Push(&stack, str[i]);
        }
    }
    Print(&stack);
    return 0;
}