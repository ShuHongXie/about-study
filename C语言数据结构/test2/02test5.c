#include <stdio.h>
#include <stdlib.h>

// 双向链表
typedef struct Node
{
  int data;
  struct Node *prior;
  struct Node *next;
} DuLNode;

DuLNode *p;

// 获取某一个结点
DuLNode *getNode(DuLNode *l, int i)
{
  printf("getnode----\n");
  p = l->next;
  int j = 0;
  if (j < i - 1)
  {
    p = p->next;
    ++j;
  }
  return p;
}

// 链表打印
void show(DuLNode *l)
{
  printf("开始打印——----\n");
  DuLNode *p = l;
  p = p->next;
  while (p != l)
  {
    printf("%d\n", p->data);
    p = p->next;
  }
  return;
}

// 插入
void insert(DuLNode *l, int i, int data)
{
  DuLNode *s = (DuLNode *)malloc(sizeof(DuLNode));
  p = getNode(l, i);
  s->data = data;
  s->prior = p->prior;
  p->prior->next = s;
  s->next = p;
  p->prior = s;
  // p = l;
  return;
}

// 删除
void delete (DuLNode *l, int i)
{
  p = getNode(l, i);
  p->prior->next = p->next;
  p->next->prior = p->prior;
  free(p);
  return;
}
// 创建
DuLNode *createList(DuLNode *l)
{
  l = (DuLNode *)malloc(sizeof(DuLNode));
  l->prior = l;
  l->next = l;
  return l;
}

int main()
{
  DuLNode *nodeList;
  nodeList = createList(nodeList);
  insert(nodeList, 1, 10);
  insert(nodeList, 1, 20);
  insert(nodeList, 1, 30);
  // insert(nodeList, 4, 40);
  delete (nodeList, 2);
  printf("------");
  show(nodeList);
  return 0;
}