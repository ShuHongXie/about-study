#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

// 循环队列(顺序形式实现)
typedef struct
{
  int *data;
  int front; // 头指针
  int rear;  // 尾指针
} sqQueue;

// 插入(入队)
void insertQueue(sqQueue *q, int e)
{
  if ((q->rear + 1) % MAXSIZE == q->front)
  {
    return;
  }
  q->data[q->rear] = e;
  q->rear = (q->rear + 1) % MAXSIZE;
  return;
}

// 删除(出队)
void pop(sqQueue *q, int e)
{
  if (q->front == q->rear)
  {
    return;
  }
  e = q->data[q->front];
  q->front = (q->front + 1) % MAXSIZE;
  return;
}

// 初始化
sqQueue *initQueue(sqQueue *q)
{
  q = (sqQueue *)malloc(sizeof(sqQueue));
  q->data = (int *)malloc(MAXSIZE * sizeof(int));
  q->front = q->rear = 0;
  return q;
}

// 获取队列长度
int getQueueLen(sqQueue *q)
{
  return (q->rear - q->front + MAXSIZE) % MAXSIZE;
}

void print(sqQueue *q)
{
  while (q->front != q->rear)
  {
    printf("%d,%d\n", q->data[q->front], q->front);
    q->front = (q->front + 1) % MAXSIZE;
  }
}

int main()
{
  sqQueue *sq;
  sq = initQueue(sq);
  insertQueue(sq, 2);
  insertQueue(sq, 3);
  insertQueue(sq, 4);
  print(sq);
  return 0;
}