#include <stdio.h>

// if语句
/*
int main()
{
  float a, b, max;
  printf("please enter a and b:");
  scanf("%f,%f", &a, &b);
  if (a > b)
    max = a;
  else
    max = b;

  printf("max=%6.2f\n", max);
  return 0;
}
*/

// switch语句
/*
int main()
{
  char grade = 'z';
  switch (grade)
  {
  case 'A':
    printf("85~100\n");
    break;
  case 'B':
    printf("10~84\n");
    break;
  default:
    printf("0分\n");
    break;
  }
  return 0;
}
*/

// 判断优先级 04.md
int main()
{
  int a = 3, b = 4, c = 5, x, y;
  int r1 = a + b > c && b == c;
  int r2 = a || b + c && b - c;
  int r3 = !(a > b) && !c || 1;
  int r4 = !(x = a) && (y == b) && 0;
  int r5 = !(a + b) + c - 1 && b + c / 2;
  printf("%d", r1); // 0
  printf("%d", r2); // 1
  printf("%d", r3); // 1
  printf("%d", r4); // 0
  printf("%d", r5); // 1
}