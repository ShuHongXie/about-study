#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

// 顺序栈的表示和实现
typedef struct Node
{
  int *data;
  int top;
  int stacksize;
} SqStack;

SqStack *intStack(SqStack *s)
{
  int arr[MAXSIZE];
  s = (SqStack *)malloc(sizeof(SqStack));
  s->data = arr;
  s->stacksize = MAXSIZE;
  s->top = 0;
  return s;
}

// 入栈
void push(SqStack *s, int e)
{
  if (s->top > s->stacksize)
  {
    printf("当前栈已满");
    return;
  }
  printf("进栈%d", e);
  s->data[s->top] = e;
  s->top++;
  return;
}

// 出栈
int pop(SqStack *s, int e)
{
  if (s->top == s->data)
  {
  }
  s->top--;
  e = s->data[s->top];
  return e;
}

// 获取栈顶元素
int getTopElem(SqStack *s, int e)
{
  return s->data[--s->top];
}

void print(SqStack *s)
{
  while (s->top > 0)
  {
    ;
    printf("%d\n", s->data[--s->top]);
  }
}

int main()
{
  SqStack *stack;
  stack = intStack(stack);
  push(stack, 2);
  push(stack, 3);
  print(stack);
  return 0;
}