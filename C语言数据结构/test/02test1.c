#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define ERROR 0
#define MAXSIZE 100 // 最大长度
int i, j;

/*
线性表的顺序存储表示(指针实现) 图书馆书籍
*/

typedef struct
{
  int no;
  char name[50];
  float price;
} Book;
typedef struct
{
  Book *elem;
  int length;
} SqList;

// 初始化线性表
void initList(SqList *l)
{
  // 构造空的顺序表l
  l->elem = (Book *)malloc(MAXSIZE * sizeof(Book));
  if (!l->elem)
  {
    printf("储存失败");
    exit(ERROR);
  }
  l->length = 0;
  return;
}

// 取值
// Book getElem(SqList l, int i, Book e)
// {
//   if (i < 1 || i > l->length)
//   {
//     printf("当前索引不存在");
//     exit(ERROR);
//   }
//   e = l->elem[i - 1];
//   return e;
// }

// 存值
void insertElem(SqList *l, int i, Book e)
{
  if (i < 1 || i > l->length + 1)
  {
    printf("超过index");
    return;
  }
  if (l->length == MAXSIZE)
  {
    return;
  }
  for (j = l->length - 1; j >= i - 1; j--)
  {
    l->elem[j + 1] = l->elem[j];
  }
  l->elem[i - 1] = e;
  ++l->length;
  return;
}

// 删除
void deleteElem(SqList *l, int i)
{
  if (i < 1 || i > l->length + 1)
  {
    return;
  }
  // printf("%d", l->length - 1);
  for (j = i; j <= l->length - 1; j++)
  {
    printf("%d, %d, %s,%s\n", j - 1, l->length - 1, l->elem[j - 1].name, l->elem[j].name);
    l->elem[j - 1] = l->elem[j];
  }
  --l->length;
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
void show(SqList *l)
{
  if (!l->length)
  {
    printf("结构体元素长度为空");
    return;
  }
  for (int i = 0; i < l->length; i++)
  {
    printf("当前图书为%s,编号为%d\n", l->elem[i].name, l->elem[i].no);
  }
}

int main()
{
  SqList list;
  initList(&list);
  // b1
  // 赋值写法1
  Book b1 = {1, "一千零一夜", 99.3};
  /*
  赋值写法2
  Book b1;
  b1.no = 1;
  strcpy(b1.name, "一千零一夜");
  b1.price = 99.3;
  */
  Book b2 = {2, "格林童话", 100};
  Book b3 = {3, "海上花", 89};
  // 插入
  insertElem(&list, 1, b1);
  insertElem(&list, 2, b2);
  insertElem(&list, 3, b3);
  show(&list);
  // 删除
  deleteElem(&list, 1);
  show(&list);
  // 获取
  int eqIndex = searchElem(list, b2);
  printf("b2和列表里面的第%d个相同\n", eqIndex);
  // printf("oo");
  return 0;
}