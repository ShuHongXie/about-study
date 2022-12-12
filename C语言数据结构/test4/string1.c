#include <stdio.h>
#include <string.h>
#define MAXLEN 35;

// 串顺序存储，分配固定长度
// typedef struct
// {
//   char ch[MAXLEN + 1]; // 存储串中的一维数组
//   int length;          // 串的长度
// }

int getIndex1(char str[], char t[], int pos)
{
  int i = pos, j = 0;
  while (i < strlen(str) && j < strlen(t))
  {
    printf("%c,%c\n", str[i], t[j]);
    if (str[i] == t[j])
    {
      ++i;
      ++j;
    }
    else
    {
      i = i - j + 1;
      printf("----%d,%d----\n", i, j);
      j = 0;
      printf("----%d,%d----\n", i, j);
    }
    printf("%d,%d\n", i, j);
  }

  if (j >= strlen(t))
  {
    return i - strlen(t) + 1;
  }
  else
  {
    return 0;
  }
}

int main()
{
  char str[] = "aaaaaba";
  char t[] = "ba";
  int index = getIndex1(str, t, 2);
  printf("str中匹配到t的字符序号为：");
  printf("%d\n", index);
}
