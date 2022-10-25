#include <stdio.h>

// int main()
// {
//   print_star();
//   print_star();
//   return 0;
// }

// void print_star()
// {
//   printf("**************\n");
// }

// int main()
// {
//   int max(int x, int y);
//   int a, b, c;
//   printf("please input two number;");
//   scanf("%d,%d", &a, &b);
//   printf("a=%d,b=%d\n", a, b);
//   c = max(a, b);
//   printf("max is %d\n", c);
//   printf("a=%d,b=%d\n", a, b);
//   return 0;
// }

// int max(int x, int y)
// {
//   int z;
//   x++;
//   y++;
//   if (x > y)
//   {
//     z = x;
//   }
//   else
//   {
//     z = y;
//   }
//   return z;
// }

int doit(int x)
{
  x = 4;
  printf("%d\n", x);
}

int main()
{
  int a[3] = {1, 3, 4};
  doit(a[0]);
  printf("%d\n", a[0]);
}