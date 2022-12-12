#include <stdio.h>
#include <string.h>
#define MAXLEN 35;

// 串顺序存储，分配固定长度
// typedef struct
// {
//   char ch[MAXLEN + 1]; // 存储串中的一维数组
//   int length;          // 串的长度
// }

int getIndex(char[] str, char[] t, int pos)
{
  int i = 1, j = 1;
  while (i <= strlen(str) && i < strlen(t))
  {
    if (str[i] == t[i])
    {
      ++i;
      ++j;
    }
    else
    {
      i = i - j + 2;
      j = 1;
    }
  }
  if (j > strlen(t))
  {
    return i - strlen(t);
  }
  else
  {
    return 0;
  }
}

int main()
{
  char str[] = "ababcabcacbab";
  char t[] = "abcac";
  // int index = index_bf(str, t, 1);
  // printf("%d", index);
}
