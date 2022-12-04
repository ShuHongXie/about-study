#include <stdio.h>

int main()
{
  // 试分析下列各算法的时间复杂度
  /* 1. O(1)
  int x = 90, y = 100;
  while (y > 0)
  {
    if (x > 100)
    {
      x = x - 10;
      y--;
    }
    else
    {
      x++;
    }
  }
  */

  /* 2. O(mn)
  for(int i =0; i < n;i++) {
   for(int j =0; j < m;j++) {
     a[i][j] = 0;
   }
  }
  */

  /* 3. O(n^2)
  int s = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      s += B[i][j];
    }
  }
  */

  /* 4. O(log3^n)
  i = 1;
  while(i < n) {
    i = i *3;
  }
  */

  /* 5. O(n^2)
   int s = 0;
   for (int i = 1; i < n; i++)
   {
     for (int j = 0; j < m-i; j++)
     {
       x++;
     }
   }
   */

  /* O(log2^n) 实际应该是n^(1/2)
  int x = n, y = 0;
  while (x >= (y + 1) * (y + 1))
  {
    y++;
  }
  */
  return 0;
}