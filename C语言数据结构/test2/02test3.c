#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define ERROR 0
#define MAXSIZE 100 // 最大长度
int i, j;

// 线性表的单链表实现 (带头结点)
// 经过一下午的实践，我发现如果结点结构体里面的data是指针类型，那么这个
// 指针在执行完会被回收，这样的话，最好是在main函数里面初始化data指针结构体
// 1.下面的例子如果Book换成int类型的话那不需要遵守这个约定
// 2.初始化函数加返回值(看02test4)
// 至少在截止22-12-06我发现了这个问题
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

// 打印
void show(BookNode *l)
{
  BookNode *p = l;
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

// 初始化, 前插法(默认空结点,增加多个数据)
void initList_H(BookNode *l, int n)
{
  // for (int i = 0; i < n; ++i)
  // {
  BookNode *node;
  node = (BookNode *)malloc(sizeof(BookNode));
  // Book *b = (Book *)malloc(sizeof(Book));
  Book b1 = {1, "一千零一夜", 99.3};
  // printf("请输入书本序号，名称，价格, 按逗号分割\n");
  // scanf("%d,%s ,%f", &b->no, &b->name[0], &b->price);
  node->data = &b1;
  node->next = l->next;
  l->next = node;
  // }
  printf("%s\n", l->next->data->name);
  printf("end------\n");
}

int main()
{
  BookNode *bookList = (BookNode *)malloc(sizeof(BookNode));
  bookList->next = NULL;
  Book b1 = {1, "一千零一夜", 99.3};
  printf("%s\n", bookList->data->name);
  // show(&bookList);

  return 0;
}