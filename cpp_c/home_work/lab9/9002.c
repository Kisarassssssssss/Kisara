#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct
{
    char bracket;
    int position;
}StackElem;

typedef struct
{
    StackElem* data;
    int top;
    int capacity;
    int max_capacity;
}Stack;

typedef enum
{
    STACK_OK,
    STACK_EMPTY,
    STACK_FULL,
    STACK_MEM_ERR
}StackResult;

StackResult stackInit(Stack* stack,int init_capacity,int max_capacity)
{
    if(init_capacity<=0||init_capacity>max_capacity)
    {
        return STACK_MEM_ERR;
    }
    stack->data=(StackElem*)malloc(sizeof(StackElem)*init_capacity);
    if(!stack->data)
    {
        return STACK_MEM_ERR;
    }
    stack->top=-1;
    stack->capacity=init_capacity;
    stack->max_capacity=max_capacity;
    return STACK_OK;
}

StackResult stackPush(Stack* stack,char bracket,int position)
{
    if(stack->top+1==stack->capacity)
    {
        if(stack->capacity>=stack->max_capacity)
        {
            return STACK_FULL;
        }
        int new_cap=stack->capacity*2;
        if(new_cap>stack->max_capacity)
        {
            new_cap=stack->max_capacity;
        }
        StackElem* new_data=(StackElem*)realloc(stack->data,sizeof(StackElem)*new_cap);
        if(!new_data)
        {
            return STACK_MEM_ERR;
        }
        stack->data=new_data;
        stack->capacity=new_cap;
    }
    stack->top++;
    stack->data[stack->top].bracket=bracket;
    stack->data[stack->top].position=position;
    return STACK_OK;
}

StackResult stackPop(Stack* stack,StackElem* elem)
{
    if(stack->top==-1)
    {
        return STACK_EMPTY;
    }
    if(elem)
    {
        elem->bracket=stack->data[stack->top].bracket;
        elem->position=stack->data[stack->top].position;
    }
    stack->top--;
    return STACK_OK;
}

StackResult stackPeek(Stack* stack,StackElem* elem)
{
    if(stack->top==-1)
    {
        return STACK_EMPTY;
    }
    if(elem)
    {
        elem->bracket=stack->data[stack->top].bracket;
        elem->position=stack->data[stack->top].position;
    }
    return STACK_OK;
}

int stackIsEmpty(const Stack* stack)
{
    return stack->top==-1?1:0;
}

void stackDestroy(Stack* stack)
{
    if(stack->data)
    {
        free(stack->data);
    }
    stack->data=NULL;
    stack->top=-1;
    stack->capacity=0;
}

int isLeftBracket(char ch)
{
    return ch=='{'||ch=='[';
}
int isRightBracket(char ch)
{
    return ch=='}'||ch==']';
}
int isBracketMatch(char left,char right)
{
    return(left=='{'&&right=='}')||(left=='['&&right==']');
}

int jsonBracketCheckBasic(const char *json_str)
{
    if(!json_str||json_str[0]=='\0')
    {
        return 1;
    }
    Stack s;
    if(stackInit(&s,1024,1000001)!=STACK_OK)
    {
        return 0;
    }
    for(int i=0;json_str[i];i++)
    {
        if(isLeftBracket(json_str[i]))
        {
            stackPush(&s,json_str[i],i);
        }
        else if(isRightBracket(json_str[i]))
        {
            StackElem e;
            if(stackPop(&s,&e)!=STACK_OK||!isBracketMatch(e.bracket,json_str[i]))
            {
                stackDestroy(&s);
                return 0;
            }
        }
    }
    int res=stackIsEmpty(&s);
    stackDestroy(&s);
    return res;
}

int jsonBracketCheckAdvanced(const char *json_str)//判断
{
    if(!json_str||json_str[0]=='\0')
    {
        return 1;
    }
    Stack s;
    if(stackInit(&s,1024,1000001)!=STACK_OK)
    {
        return 0;
    }
    int in_str=0,esc=0;
    for(int i=0;json_str[i];i++)
    {
        char c=json_str[i];
        if(in_str)
        {
            if(esc)
            {
                esc=0;
            }
            else if(c=='\\')
            {
                esc=1;
            }
            else if(c=='"')
            {
                in_str=0;
            }
        }
        else
        {
            if(c=='"')
            {
                in_str=1;
            }
            else if(isLeftBracket(c))
            {
                stackPush(&s,c,i);
            }
            else if(isRightBracket(c))
            {
                StackElem e;
                if(stackPop(&s,&e)!=STACK_OK||!isBracketMatch(e.bracket,c))
                {
                    stackDestroy(&s);
                    return 0;
                }
            }
        }
    }
    int res=(stackIsEmpty(&s)&&!in_str);
    stackDestroy(&s);
    return res;
}

int main()
{
    static char str[1000001];
    if(!fgets(str,1000001,stdin))
    {
        return 0;
    }
    str[strcspn(str,"\r\n")]=0;
    int result1=jsonBracketCheckBasic(str);
    int result2=jsonBracketCheckAdvanced(str);
    printf("%d %d",result1,result2);
    return 0;
}