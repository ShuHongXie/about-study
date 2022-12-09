#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

// 链栈的表示和实现
// 对于所有结构体指针，只要结构体传入后参数的位置变了，就必须返回结构体，不然会被回收
typedef struct Node
{
  int data; // 变成链表之后 这里只放单个数值，不再存放数组，所以可以不用指针
  struct Node *next;
} SqStack;

SqStack *p;

// 初始化
SqStack *intStack(SqStack *s)
{
  s = (SqStack *)malloc(sizeof(SqStack));
  s->next = NULL;
  return s;
}

// 入栈
SqStack *push(SqStack *s, int e)
{
  SqStack *p = (SqStack *)malloc(sizeof(SqStack));
  if (!p)
  {
    printf("空间申请失败");
  }
  p->data = e;
  p->next = s;
  s = p;
  // printf("%d\n", s->data);
  return s;
}

// 出栈
int pop(SqStack *s)
{
  if (s == NULL)
  {
    printf("当前栈已空");
    return 0;
  }
  int e = s->data;
  p = s;
  s = s->next;
  free(p);
  return e;
}

// 取栈顶元素
int getTopElem(SqStack *s)
{
  if (s != NULL)
  {
    printf("%d\n", s->data);
    return s->data;
  }
}

void print(SqStack *s)
{
  printf("进入打印逻辑\n");
  p = s;
  while (p->next)
  {
    printf("%d\n", p->data);
    p = p->next;
  }
  return;
}

void traverseList(SqStack *s)
{
}

int main()
{
  SqStack *stack;
  stack = intStack(stack);
  stack = push(stack, 2);
  stack = push(stack, 3);
  print(stack);
  return 0;
}