#include <stdio.h>
#include <math.h>

int main()
{
  int i = 100;
  for (; i <= 200; i++)
  {
    // 取平方根
    int k = (int)sqrt(i);
    // printf("%d\n", k);
    int j;
    for (j = 2; j <= k; j++)
    {
      // printf("%d\n", i % j);
      if (i % j == 0)
      {
        break;
      }
      // printf("%d,%d\n", j, k);
      if (j == k)
      {
        printf("%d是素数\n", i);
      }
    }
  }
}