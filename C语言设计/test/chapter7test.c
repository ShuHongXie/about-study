#include <stdio.h>
#include <string.h>

int main()
{
  void maxCommonYue();
  void minCommonBei();
  void isSuNum();
  void formatArray();
  void stringReserve();
  // maxCommonYue();
  // minCommonBei();
  // isSuNum();
  // formatArray();
  stringReserve();
  return 0;
}

// 7.1-1. 求两个整数的最大公约数
void maxCommonYue()
{
  int a, b;
  int yueNum = 0; // 被约数
  scanf("%d,%d", &a, &b);
  int lessNum = a >= b ? b : a; // 较小的那个值
  for (yueNum = lessNum; yueNum > 0; yueNum--)
  {
    if (a % yueNum == 0 && b % yueNum == 0)
    {
      printf("a和b的最大公约数为%d\n", yueNum);
      break;
    }
  }
}

// 7.1-2. 求两个整数的最小公倍数
void minCommonBei()
{
  int a, b;
  int beiNum = 1; // 倍数
  int isFindBei = 0;
  scanf("%d,%d", &a, &b);
  printf("a=%d,b=%d", a, b);
  int lessNum = a >= b ? b : a;
  int maxNum = a <= b ? b : a;
  for (; beiNum > 0; beiNum++)
  {
    if (isFindBei)
    {
      break;
    }
    int expandLess = lessNum * beiNum;
    for (int i = 1; i > 0; i++)
    {
      int expandMax = maxNum * i;
      if (expandMax == expandLess)
      {
        isFindBei = 1;
        printf("a和b的最小公倍数为%d\n", expandMax);
        break;
      }
      else if (expandMax > expandLess)
      {
        break;
      }
    }
  }
}

// 7.2. 判断一个整数是否为素数
void isSuNum()
{
  printf("请输入你要判断整数");
  int a;
  scanf("%d", &a);
  for (int i = a - 1; i > 1; i--)
  {
    if (a % i == 0)
    {
      printf("%d不是素数", a);
      break;
    }
    if (i == 2)
    {
      printf("%d是素数", a);
    }
  }
}

// 7.3. 给定一个3x3的二维整型数组转置，即行列互换
void formatArray()
{
  int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  for (int i = 0; i < 3; i++)
  {
    for (int j = i; j < 3; j++)
    {
      int num = arr[i][j];
      arr[i][j] = arr[j][i];
      arr[j][i] = num;
    }
  }
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {

      printf("%d\n", arr[i][j]);
    }
  }
}

// 7.4 写一个函数，使输入的函数反序存在，如"CANADA", 输出""ANANAC"
void stringReserve()
{
  printf("颠倒字符串，请输入您的字符串\n");
  char strReserve[10000];
  char str[10000];
  gets(str);
  int len = strlen(str);
  for (int i = 0; i < len; i++)
  {
    strReserve[i] = str[len - i - 1];
  }

  printf("颠倒字符串后为\n");
  puts(strReserve);
  printf("\n");
}