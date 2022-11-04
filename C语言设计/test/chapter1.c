#include <stdio.h>

int main()
{
  int a = 2, b = 3, c = 4;
  a = b++ / 1 * 4 + b + --b;
  printf("%d,%d\n", a, b);
  return 0;
}