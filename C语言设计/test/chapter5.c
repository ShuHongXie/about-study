#include <stdio.h>

int fibonacci(int n)
{
  if (n <= 2)
  {
    return 1;
  }
  else
  {
    return fibonacci(n - 1) + fibonacci(n - 2);
  }
}

// 求100以内斐波那契数列
int main()
{
  int n;
  scanf("%d", &n);
  printf("%d\n", fibonacci(n));
  return 0;
}

// 求1到100相加
// for循环
// int main()
// {
//   int sum = 0;
//   for (int i = 1; i <= 100; i++)
//   {
//     sum += i;
//   }
//   printf("%d\n", sum);
//   return 0;
// }

// 1.while
// int main()
// {
//   int i = 1, sum = 0;
//   while (i <= 100)
//   {
//     sum += i;
//     printf("%d,%d\n", sum, i);
//     i++;
//   }
//   printf("%d\n", sum);
//   return 0;
// }

// do..while
// int main()
// {
//   int i = 1, sum = 0;
//   do
//   {
//     sum += i;
//     i++;
//   } while (i <= 100);

//   printf("%d\n", sum);
//   return 0;
// }