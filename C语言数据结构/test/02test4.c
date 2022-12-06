#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define ERROR 0
#define MAXSIZE 100 // 最大长度

// 线性表的单链表实现 (带头结点)
typedef struct Node
{
  int data;
  struct Node *next;
} BookNode;

// 打印
void show(BookNode *l)
{
  printf("开始打印——----\n");
  BookNode *p = l;
  while (p->next)
  {
    printf("%d\n", p->data);
    p = p->next;
  }
  return;
}

// 初始化, 前插法(默认空结点,增加多个数据)
BookNode *initList_H(BookNode *l, int n)
{
  l = (BookNode *)malloc(sizeof(BookNode));
  l->next = NULL;
  BookNode *node;
  for (int i = 0; i < n; ++i)
  {
    node = (BookNode *)malloc(sizeof(BookNode));
    node->data = i + 1;
    node->next = l->next;
    l->next = node;
  }
  return l;
}

// 初始化, 后插法(默认空结点,增加多个数据)
BookNode *initList_R(BookNode *l, int n)
{
  l = (BookNode *)malloc(sizeof(BookNode));
  l->next = NULL;
  BookNode *node;
  for (int i = 0; i < n; ++i)
  {
    node = (BookNode *)malloc(sizeof(BookNode));
    node->data = i + 1;
    node->next = NULL;
    l->next = node;
    l = node;
  }
  return l;
}

int main()
{
  BookNode *bookList;
  // bookList = initList_H(bookList, 4);
  bookList = initList_R(bookList, 4);
  printf("%d\n", bookList->data);
  show(bookList);
  return 0;
}