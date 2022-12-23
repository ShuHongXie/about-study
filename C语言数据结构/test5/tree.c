#include <stdio.h>

// 二叉树不太适合用顺序结构表示，会占用太多空间，所以使用链表
// 二叉树的链表展示
typedef struct BitNode
{
  int data;
  struct BitNode *lchild, *rchild;
} BitNode;

int main()
{
  int z = 073;
  printf("%d\n", z++);
}