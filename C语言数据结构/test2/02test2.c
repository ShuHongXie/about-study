/*
 * @Author: 谢树宏 384180258@qq.com
 * @Date: 2022-12-05
 * @LastEditors: 谢树宏 384180258@qq.com
 * @LastEditTime: 2022-12-06
 * @FilePath: /C语言数据结构/test/02test2.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define ERROR 0
#define MAXSIZE 100 // 最大长度
int i, j;

// 线性表的单链表实现 (带头结点)
typedef struct
{
  int no;
  char name[50];
  float price;
} Book;

typedef struct Node
{
  Book *data;
  struct Node *next;
} BookNode;

// 插入
void insertBook(BookNode *l, int i, Book *e)
{
  int j = 0;
  BookNode *p = l;
  while (p && j < i - 1)
  {
    ++j;
    p = p->next;
  }
  if (!p || j > i - 1)
  {
    return;
  }
  BookNode *node;
  node = (BookNode *)malloc(sizeof(BookNode)); // 分配相应的内存空间
  node->data = e;
  node->next = p->next;
  p->next = node;
  return;
}

// 删除
void deleteBook(BookNode *l, int i)
{
  BookNode *p = l;
  BookNode *retainNode; // 待删除的项
  int j = 0;
  while (p->next && j < i - 1)
  {
    p = p->next;
    ++j;
  }
  retainNode = p->next;
  p->next = retainNode->next;
  free(retainNode);
  retainNode = NULL;
  return;
}

// 获取指定index的结点值
void getElem(BookNode *l, int i)
{
  BookNode *p = l->next;
  j = 0;
  while (p && j < i)
  {
    p = p->next;
    j++;
  }
  if (!p || j > i)
  {
    return;
  }
  return;
}

// 打印
void show(BookNode *l)
{
  BookNode *p = l;
  // printf("%s\n", p->next->data->name);
  while (p != NULL)
  {
    if (p->data != NULL)
    {
      printf("%s\n", p->data->name);
    }
    p = p->next;
  }
  return;
}

// 初始化(默认空结点)
void initList(BookNode *l)
{
  l = (BookNode *)malloc(sizeof(BookNode));
  l->next = NULL;
  return;
}

int main()
{

  BookNode bookList;
  initList(&bookList);
  // 插入
  Book b1 = {1, "一千零一夜", 99.3};
  Book b2 = {2, "格林童话", 100};
  Book b3 = {3, "海上花", 89};
  insertBook(&bookList, 1, &b1);
  insertBook(&bookList, 2, &b2);
  insertBook(&bookList, 3, &b3);
  // 删除
  deleteBook(&bookList, 2);
  // 打印
  show(&bookList);
  // getElem(&bookList, 2);

  return 0;
}