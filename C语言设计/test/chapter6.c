#include <stdio.h>
#include <string.h>

// 找出三个字符串中的最大者

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

/*
int main()
{
  // char a[10] = {'H', 'a', 'p', 'p', 'y'};
  // char b[10] = {"Happy"};
  // char c[10] = "Happy";
  // char d[10] = {'H', 'a', 'p', 'p', 'y'};
  // char e[10] = "   ";
  // printf("%d\n", strlen(a));
  // printf("%d\n", strlen(b));
  // printf("%d\n", strlen(c));
  // printf("%d\n", strlen(d));
  // printf("%d\n", strlen(e));

  // 判断大小
  // char a[] = "girl";
  // char b[] = "goal";
  // printf("%d\n", strlen(a));
  // printf("%d\n", strcmp(a, b));

  // puts gets
  // char a[] = "";
  // char b[] = "";
  // gets(a);
  // puts(a);
  return 0;
}
**/