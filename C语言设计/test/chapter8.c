#include <stdio.h>

// int main()
// {
//   int a, b;
//   int *p1, *p2; // 定义指针变量
//   a = 100, b = 10;
//   p1 = &a; // 把a的地址赋值给p1
//   p2 = &b; // 同上
//   printf("a=%d,b=%d\n", a, b);
//   printf("p1=%d,p2=%d\n", *p1, *p2); // 输出指针变量所指向的整型变量的值
//   printf("p1=%d,p2=%d\n", p1, p2);   // 输出指针变量所指向的整型变量的值
//   return 0;
// }

// int main()
// {
//   int a = 100;
//   int *p1 = &a; // 定义指针变量
//   // *p1 = 2;
//   printf("a=%d\n", a);
//   printf("p1=%d\n", *p1);
//   printf("p1=%o\n", p1);
//   return 0;
// }

// 指针变量互换 按先打后小输出
// int main()
// {
//   int a, b, *p1, *p2, *p;
//   scanf("%d,%d", &a, &b);
//   p1 = &a;
//   p2 = &b;
//   if (a < b)
//   {
//     p = p1;
//     p1 = p2;
//     p2 = p;
//   }
//   printf("a=%d,b=%d\n", a, b);
//   printf("max=%d,min=%d\n", *p1, *p2);
//   return 0;
// }

// 指针变量互换 大小调整 函数方式
// 这里会非常迷惑人
// int main()
// {
//   void swap(int *p1, int *p2);
//   int a, b, *p1, *p2, *p;
//   scanf("%d,%d", &a, &b);
//   p1 = &a;
//   p2 = &b;
//   if (a < b)
//   {
//     swap(p1, p2);
//   }
//   printf("max=%d,min=%d\n", a, b);
//   return 0;
// }

/**
void swap(int *p1, int *p2)
{
  printf("%d,%d\n", *p1, *p2);
  printf("%d,%d\n", p1, p2);
  // 交换的形式1 利用值传递 从上面传进来的时候 整个*p1=a的值(不是指向) p1才指向a
  // 可以理解为这里类似于js数组 ，因为*号指针标识的原因使其附带了指针功能(即改变值不改变指向)
  int temp;
  temp = *p1;
  *p1 = *p2;
  *p2 = temp;
  // （不生效）交换的形式2 利用指针指向功能 利用指针地址修改
  // 不能通过执行调用函数来改变实参指针变量的值(p1=p2不会生效)，但是
  // 可以改变实参指针变量所指的变量的值(上面的*p1=*p2)
  int *temp;
  temp = p1;
  p1 = p2;
  p2 = temp;
}

*/

// 数组指针打印

/*
int main()
{
  int a[10] = {19, 17, 29, 23, 11, 52, 19};
  int i, *p = a;
  // for (i = 0; i < 10; i++)
  // {
  //   // 通过数组名计算数组元素地址，找到元素
  //   printf("%d\n", a + i);
  //   printf("%d\n", *(a + i));
  //   printf("\n");

  //   // 通过指针变量计算数组元素地址，找到元素
  //   // printf("%d\n", p + i);
  //   // printf("%d\n", *(p + i));
  // }
  // 用指针变量先后指向各数组元素
  for (; p < (a + 10); p++)
  {
    printf("%d", *p);
    printf("%d", p);
    printf("\n");
  }
  return 0;
}

*/

// 通过指针变量读入数组的10个元素，然后输出这10个元素，p指针循环的位置
/*
int main()
{
  int *p, i, a[3];
  p = a;
  for (i = 0; i < 3; i++)
  {
    scanf("%d", p++);
  }
  // 上面经过一轮循环 指针已经到了a[10]了，所以下面继续打印的话 无法知道值是多少
  // 解决方法是下面 p=a 这样p指向的地址就变回了a[0]
  p = a;
  for (i = 0; i < 3; i++, p++)
  {
    printf("%d\n", *p);
    printf("%d\n", *(a + i));
  }
  printf("\n");
  return 0;
}
*/

// 数组颠倒
// int main()
// {
//   // void inv(int x[], int n);
//   void inv(int *arr, int n);
//   int i, a[10] = {3, 7, 9, 11, 0, 6, 7, 5, 4, 2};
//   printf("the original arry:\n");
//   for (i = 0; i < 10; i++)
//   {
//     printf("%d", a[i]);
//   }
//   printf("\n");
//   inv(a, 10);
//   printf("the array has been inverted:\n");
//   for (i = 0; i < 10; i++)
//   {
//     printf("%d", a[i]);
//   }
//   printf("\n");
//   return 0;
// }

// void inv(int *arr, int n)
// {
//   int *temp, i, j, m = (n - 1) / 2;
//   for (i = 0; i < m; i++)
//   {
//     j = n - 1 - i;
//     *temp = *(arr + i);
//     *(arr + i) = *(arr + j);
//     *(arr + j) = *temp;
//   }
// }

// 版本1
// void inv(int x[], int n)
// {
//   int temp, i, j, m = (n - 1) / 2;
//   for (i = 0; i < m; i++)
//   {
//     j = n - 1 - i;
//     temp = x[i];
//     x[i] = x[j];
//     x[j] = temp;
//   }
// }

// 版本2
// void inv(int *x, int n)
// {
//   int *p, temp, *i, *j, m = (n - 1) / 2;
//   i = x;
//   j = x + n - 1;
//   p = x + m;
//   for (; i < p; i++, j--)
//   {
//     temp = *j;
//     *i = *j;
//     *j = temp;
//   }
//   return;
// }

int main()
{

  int p = 1;
  int *a = &p;
  int *arr = {1, 2, 3};
  char *string = "i love china";
  // printf("%c\n", string);
  // printf("%d\n", arr);
  printf("%d\n", a);
  printf("%d\n", *a);
}

// 字符串复制 下标法
// int main()
// {
//   char a[] = "I am a boy.", b[20];
//   int i;
//   for (i = 0; *(a + i) != '\0'; i++)
//   {
//     *(b + i) = *(a + i);
//   }
//   *(b + i) = '\0';
//   printf("string a is :%s\n", a);
//   printf("string a is :");
//   for (i = 0; b[i] != '\0'; i++)
//   {
//     printf("%c", b[i]);
//   }
//   printf("\n");
//   return 0;
// }

// 字符串复制 指针变量法
// int main()
// {
//   char a[] = "I am a boy.", b[20];
//   int i, *p1 = a, *p2 = b;
//   for (; *p1 != '\0'; p1++, p2++)
//   {
//     *p2 = *p1;
//   }
//   *p2 = '\0';
//   printf("string a is :%s\n", a);
//   printf("string a is :");
//   for (i = 0; b[i] != '\0'; i++)
//   {
//     printf("%c", b[i]);
//   }
//   printf("\n");
//   return 0;
// }

// %s测试
// int main()
// {
//   char a[10] = "123456789";
//   char *p = a;
//   p = a + 6;
//   printf("%s\n", p);
//   return 0;
// }