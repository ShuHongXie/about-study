#include <stdio.h>
#define MAXSIZE 100 // 最大长度

// 线性表的顺序存储表示 图书馆书籍
typedef struct
{
  char no[20];
  char name[50];
  float price;
} Book;
typedef struct
{
  Book *elem;
  int length;
} SqList;

Status InitList(SqList &L)
{
  L.elem = new Book[MAXSIZE]
  if(L.elem) exit(OVERFLO)
}

int main()
{
  printf("oo");
  return 0;
}