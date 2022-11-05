#include <stdio.h>

// getchar putchar使用

int main()
{
  char a, b, c;
  a = getchar();
  b = getchar();
  c = getchar();
  putchar(a);
  putchar(b);
  putchar(c);
  putchar('\n');
  return 0;
}

// scanf使用
/*
int main()
{
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  printf("a=%d,b=%d,c=%d\n", a, b, c);
  return 0;
}
*/

// 无符号数据和有符号数据之间的赋值
// int main()
// {
//   unsigned short a;
//   short int b;
//   b = -1;
//   a = b;
//   printf("%u\n", a); // 65535
//   return 0;
// }

// int main()
// {
//   int a = 123, b = 12345;
//   printf("%d,%4d", a, b); // 65535
//   return 0;
// }