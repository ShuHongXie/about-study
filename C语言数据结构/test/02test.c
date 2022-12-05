#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define ERROR 0
#define MAXSIZE 100 // 最大长度
int i, j;

/*
线性表的顺序存储表示(非指针实现) 图书馆书籍
单纯使用结构体传参的话是无法改变参数的值的，下面的代码是错误师范，得使用
指针来解决这个问题，看02test1.c
*/

typedef struct
{
  int no;
  char name[50];
  float price;
} Book;
typedef struct
{
  Book elem[MAXSIZE];
  int length;
} SqList;

// 初始化线性表
void initList(SqList l)
{
  // 构造空的顺序表l
  // l.elem = (Book *)malloc(MAXSIZE * sizeof(Book));
  // if (!l.elem)
  // {
  //   printf("储存失败");
  //   exit(ERROR);
  // }
  l.length = 0;
  printf("%d\n", l.length);
  return;
}

// 取值
Book getElem(SqList l, int i, Book e)
{
  if (i < 1 || i > l.length)
  {
    printf("当前索引不存在");
    exit(ERROR);
  }
  e = l.elem[i - 1];
  return e;
}

// 存值
void insertElem(SqList l, int i, Book e)
{
  if (i < 1 || i > l.length + 1)
  {
    printf("超过index");
    return;
  }
  if (l.length == MAXSIZE)
  {
    return;
  }
  printf("%d,%d\n", i, l.length);
  for (j = l.length - 1; j >= i - 1; j--)
  {
    l.elem[j + 1] = l.elem[j];
  }
  l.elem[i - 1] = e;
  // ++l.length;
  // printf("%d\n", l.length);
  printf("%s\n", e.name);
  return;
}

// 删除
void deleteElem(SqList l, int i)
{
  if (i < 1 || i > l.length + 1)
  {
    return;
  }
  for (j = i; j < l.length - 1; j++)
  {
    l.elem[j - 1] = l.elem[j];
  }
  --l.length;
  return;
}

// 查找
int searchElem(SqList l, Book e)
{
  for (i = 0; i < l.length; i++)
  {
    if (l.elem[i].no == e.no)
    {
      return i + 1;
    }
  }
  return 0;
}

// 打印
void show(SqList l)
{
  if (!l.length)
  {
    printf("结构体元素长度为空");
    return;
  }
  for (int i = 0; i < l.length; i++)
  {
    printf("当前图书为%s,编号为%d\n", l.elem[i].name, l.elem[i].no);
  }
}

int main()
{
  SqList list;
  initList(list);
  printf("%d\n", list.length);
  // Book a1;
  // a1.no = 1;
  // strcpy(a1.name, "一千零一夜");
  // a1.price = 99.3;
  // // Book a2 = {2, "格林童话", 100};
  // insertElem(list, 1, a1);
  // printf("%s\n", a1.name);
  // insertElem(list, 2, a2);
  // show(list);
  // printf("oo");
  return 0;
}