#include <stdio.h>
#include <math.h>

// getchar putchar使用

// int main()
// {
//   char a, b, c;
//   // 形式1
//   // a = getchar();
//   // b = getchar();
//   // c = getchar();
//   // putchar(a);
//   // putchar(b);
//   // putchar(c);

//   // 形式2
//   putchar(getchar());
//   putchar(getchar());
//   putchar(getchar());
//   putchar('\n');
//   return 0;
// }

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
//   printf("%4d,%4d", a, b); // 65535
//   return 0;
// }

// int main()
// {
//   double a, b, c, s, area;
//   scanf("%lf,%lf,%lf", &a, &b, &c);
//   s = (a + b + c) / 2.0;
//   area = sqrt(s * (s - a) * (s - b) * (s - c));
//   printf("a   =%7.2f\nb   =%7.2f\nc   =%7.2f\narea=%7.2f\n", a, b, c, area);
//   return 0;
// }

int main()
{
  unsigned short a = 65535;
  short int b = -2;
  printf("a=%d,%o,%x,%u\n", a, a, a, a);
  printf("b=%d,%o,%x,%u\n", b, b, b, b);
  char c[] = "CHINA";
  printf("%3s,%7.2s,%.4s,%-5.3s\n", c, c, c, c);
  float f = 123.456;
  return 0;
}