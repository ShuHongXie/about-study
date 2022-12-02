#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  void orderThreeInteger();
  void orderThreeString();
  void formatFour();
  void moveMn(int n, int m);
  void getStringLen();
  void formatNewStr();
  // orderThreeInteger();
  // orderThreeString();
  // formatFour();
  // moveMn(6, 2);
  // getStringLen();
  formatNewStr();
  return 0;
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

// 8-4. 有n个整数，使前面各数顺序向后移动m个位置，最后m个数变成前面m个数。
// 写一函数实现以上功能，在主函数中输入n个整数和输出调整后的n个数。
void moveMn(int n, int m)
{
  printf("%d,%d\n", n, m);
  printf("请输入数组元素\n");
  int arr[n];
  int i;
  for (i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }
  int moveArr[m];
  for (i = 0; i < m; i++)
  {
    *(moveArr + i) = *(arr + n - m + i);
  }
  // printf("%d\n", n - m);
  // printf("-----\n");
  for (i = n; i > m; i--)
  {
    *(arr + i - 1) = *(arr + i - m - 1);
  }
  // printf("转移%d个数后的值为\n", m);
  for (i = 0; i < n; i++)
  {
    if (i < m)
    {
      *(arr + i) = *(moveArr + i);
    }
    printf("%d", *(arr + i));
  }
}

// 8-5. 有n个学生围成一排，顺序排号，从第一个学生开始报数(从1到3报数),凡报到3的学生退出圈子，
// 到最后只留下一名学生，问最后留下来的是第几名

// 8-6，编写一函数，求字符串的长度，在函数中输入字符串，并求其长度
void getStringLen()
{
  // char c[100];
  // gets(c);
  // char *p = c;
  // printf("%d", strlen(p));
}

// 8-7. 字符串a内容为My name is Li jilin，字符串b内容为Mr Zhang HaoLing is very happy.
// 写一个函数将字符串b中的5-17个字符即Zhang Haoling赋值到字符串a中，取代Li jinlin,输出新的字符串a

void formatNewStr()
{
  char a1[100] = "My name is Li jilin";
  char a2[] = "Mr Zhang HaoLing is very happy";
  char a3[20] = "";
  char *p1 = a1, *p2 = a2;
  char *p3 = a3;
  int i = 0;
  // 指针写法
  for (; *p2 != '\0'; p2++, i++)
  {

    if (i >= 3 && i <= 16)
    {
      *p3 = *p2;
      if (i == 16)
      {
        *p3 = '\0'; // p3表示结束
        break;
      }
      else
      {
        p3++;
      }
    }
  }
  p3 = a3; // 指针指回第一个
  for (i = 0; i < 100; p1++, i++)
  {
    if (i >= 11)
    {
      *p1 = *p3;
      p3++;
    }
  }
  p1 = a1;
  for (; *p1 != '\0'; p1++)
  {
    printf("%c", *p1);
  }
  printf("\n");
  printf("a1=%s\n", a1);
  printf("a3=%s\n", a3);
}