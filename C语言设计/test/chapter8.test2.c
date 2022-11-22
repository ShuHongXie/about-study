#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
  void orderThreeInteger();
  void orderThreeString();
  void formatFour();
  // orderThreeInteger();
  // orderThreeString();
  formatFour();
}

// 8-1.输入3个整数，按从小到大顺序输出
void orderThreeInteger()
{
  void sortInt(int *num1, int *num2);
  int a, b, c;
  scanf("%d,%d,%d", &a, &b, &c);
  int *p1 = &a, *p2 = &b, *p3 = &c;
  if (*p1 > *p2)
    sortInt(p1, p2);
  if (*p1 > *p3)
    sortInt(p1, p3);
  if (*p2 > *p3)
    sortInt(p2, p3);
  printf("整数从小到大排序为%d,%d,%d", *p1, *p2, *p3);
}

void sortInt(int *num1, int *num2)
{
  int temp;
  temp = *num1;
  *num1 = *num2;
  *num2 = temp;
}

// 8-2.输入3个字符串，按从小到大顺序输出
void orderThreeString()
{
  void sortString(char *c1, char *c2);
  char a1[100], a2[100], a3[100];
  gets(a1);
  gets(a2);
  gets(a3);
  if (strcmp(a1, a2) > 0)
    sortString(a1, a2);
  if (strcmp(a1, a3) > 0)
    sortString(a1, a3);
  if (strcmp(a2, a3) > 0)
    sortString(a2, a3);
  printf("字符串从小到大排序为%s,%s,%s", a1, a2, a3);
}

void sortString(char *c1, char *c2)
{
  char temp[100];
  strcpy(temp, c1);
  strcpy(c1, c2);
  strcpy(c2, temp);
}

// 8-3.输入10(这里只写4个)个整数，将其中最小的数和第一个数对换，把最大的数和最后一个数对换
void formatFour()
{
  void formatMax(int arr[], int max, int min);
  printf("请输入4个整数");
  int arr[4], i;
  for (i = 0; i < 4; i++)
  {
    scanf("%d", &arr[i]);
  }
  int max = arr[0];
  int min = arr[0];
  printf("%d,%d", max, min);
  printf("进入循环逻辑\n");
  formatMax(arr, max, min);
  for (i = 0; i < 4; i++)
  {
    printf("%d", *(arr + i));
  }
}

void formatMax(int arr[], int max, int min)
{

  int i, temp;
  for (i = 0; i < 4; i++)
  {

    if (max < *(arr + i))
    {
      max = *(arr + i);
    }
    if (min > *(arr + i))
    {
      min = *(arr + i);
    }
  }
  printf("最大值为%d，最小值为%d\n", max, min);
  for (i = 0; i < 4; i++)
  {
    if (*(arr + i) == max)
    {
      temp = *(arr + i);
      *(arr + i) = *(arr + 3);
      *(arr + 3) = temp;
    }
    else if (*(arr + i) == min)
    {
      temp = *(arr + i);
      *(arr + i) = *(arr + 0);
      *(arr + 0) = temp;
    }
  }
}