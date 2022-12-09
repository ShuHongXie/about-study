#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

// 循环队列(顺序形式实现)
typedef struct QNode
{
  int data;
  struct QNode *next;
} QNode;

typedef struct
{
  QNode *front;
  QNode *rear;
} LinkQueue;

QNode *p;

// 入队(添加)
void insertQueue(LinkQueue *q, int e)
{
  p = (QNode *)malloc(sizeof(QNode));
  p->data = e;
  p->next = NULL;
  q->rear->next = p;
  q->rear = p;
  return;
}

// 出队(删除)
void popQueue(LinkQueue *q, int e)
{
  if (q->front == q->rear)
  {
    printf("队列为空");
    return;
  }
  p = q->front->next;
  e = p->data;
  q->front->next = p->next;
  if (q->rear == p)
  {
    q->rear = q->front;
  }
  free(p);
  return;
}

// 初始化
LinkQueue *initQueue(LinkQueue *q)
{
  q = (LinkQueue *)malloc(sizeof(LinkQueue));
  q->front = q->rear = (QNode *)malloc(sizeof(QNode));
  q->front->next = NULL;
  return q;
}

int main()
{
  LinkQueue *sq;
  sq = initQueue(sq);
  insertQueue(sq, 2);
  insertQueue(sq, 3);
  // insertQueue(sq, 4);
  // print(sq);
  return 0;
}