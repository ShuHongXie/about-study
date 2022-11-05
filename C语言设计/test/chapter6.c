#include <stdio.h>
#include <string.h>

// 找出三个字符串中的最大者
/*
int main()
{
  char string[20];
  char str[3][20];
  int i;
  for (i = 0; i < 3; i++)
  {
    // 类似于scanf 在终端获取到字符串
    gets(str[i]);
  }
  // 第一次比较 找出2个的最大值 赋值
  if (strcmp(str[0], str[1]) > 0)
  {
    strcpy(string, str[0]);
  }
  else
  {
    strcpy(string, str[1]);
  }
  // 再次比较 赋值
  if (strcmp(str[2], string) > 0)
  {
    strcpy(string, str[2]);
  }
  printf("最长的是\n%s\n", string);
  return 0;
}
*/

int main()
{
  // char a[] = "waitwait";
  // int len = strlen(a);
  // printf("%d\n", strlen(a));

  char str1[30] = "people republic of ";
  char str2[] = "chaina";
  // 字符串合并
  printf("%s\n", strcat(str1, str2));
  // 字符串比较
  printf("%d\n", strcmp(str1, str2));
  return 0;
}