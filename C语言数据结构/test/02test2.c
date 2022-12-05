#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define ERROR 0
#define MAXSIZE 100 // 最大长度
int i, j;

// 线性表的单链表实现 ()
typedef struct
{
  int no;
  char name[50];
  float price;
} Book;

typedef struct BookNode
{
  Book data;
  struct BookNode *next;
} BookNode;

// 插入
void insertBook(BookNode *l, int i, Book e)
{
  int j = 0;
  BookNode *p = l;
  while (p && j < i - 1)
  {
    ++j;
    p->p->next;
  }
  if (!p || j > i - 1)
  {
    return ERROR;
  }
  BookNode node;
  node->data = e;
  node->next = p->next;
  p - next = node;
  return;
}

// 获取指定index的结点值
BookNode getElem(BookNode l, int i)
{
  BookNode *p = l.next;
  j = 1;
  while (p && j < i)
  {
    p = p->next;
    j++;
  }
  if (!p || j > i)
  {
    return ERROR;
  }
  return *p;
}

// 初始化
void initList(BookNode *l)
{
  // l = (Book *)malloc(MAXSIZE * sizeof(Book));
  l->next = NULL;
  return;
}

void main()
{
  BookNode bookList;
  initList(&bookList);
  return;
}