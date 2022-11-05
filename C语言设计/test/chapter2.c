#include <stdio.h>
#include <math.h>
#define PI 3.14153423

// 鸡兔同笼问题
int main()
{
  long double f = 3.61232131232132121323321312;
  float test = 3.1415926;
  float test1 = 1234.131602;
  char a = 'a';
  char a1[] = "a";
  int b = 3;
  double b1 = (double)b;
  double b2 = 3.14123215311242;
  int i;
  i = (int)f;
  printf("f=%f,i=%d\n", f, i);
  // printf("%d", sizeof(f));
  // printf("%f\n", test);
  // printf("%f", test1);
  // printf("%c\n", a);
  printf("%d\n", sizeof(a));
  printf("%d\n", sizeof(a1));
  printf("%.4f\n", b1);
  printf("%.16f\n", b2);
  return 0;
}