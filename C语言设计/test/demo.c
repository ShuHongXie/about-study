#include <stdio.h>

int main()
{
  long long sum = 1;
  int i = 1;
  for (; i <= 100; i++)
  {
    printf("%d,%e", i, sum);
    sum *= i;
  }
  printf("%d\n", sum);
  printf("%d", 123);
  return 0;
}