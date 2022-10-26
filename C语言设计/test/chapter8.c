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

// 指针变量互换 大小调整
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
//     printf("a=%d,b=%d\n", a, b);
//     printf("max=%d,min=%d\n", *p1, *p2);
//   }
//   return 0;
// }

// 指针变量互换 大小调整 函数方式
// 这里会非常迷惑人
int main()
{
  void swap(int *p1, int *p2);
  int a, b, *p1, *p2, *p;
  scanf("%d,%d", &a, &b);
  p1 = &a;
  p2 = &b;
  if (a < b)
  {
    swap(p1, p2);
  }
  printf("max=%d,min=%d\n", a, b);
  return 0;
}

void swap(int *p1, int *p2)
{
  printf("%d,%d\n", *p1, *p2);
  printf("%d,%d\n", p1, p2);
  // 交换的形式1 利用值传递 从上面传进来的时候 整个*p1=a的值(不是指向) p1才指向a
  // 可以理解为这里类似于数组 ，因为*号指针标识的原因使其附带了指针功能
  // int temp;
  // temp = *p1;
  // *p1 = *p2;
  // *p2 = temp;
  // （不生效）交换的形式2 利用指针指向功能 利用指针地址修改
  // 不能通过执行调用函数来改变实参指针变量的值(p1=p2不会生效)，但是
  // 可以改变实参指针变量所指的变量的值(上面的*p1=*p2)
  int *temp;
  temp = p1;
  p1 = p2;
  p2 = temp;
}