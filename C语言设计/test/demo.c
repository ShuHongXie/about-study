#include <stdio.h>
#include <string.h>

int main()
{
  void formatNewStr();
  formatNewStr();
  return 0;
}

void formatNewStr()
{
  char a1[100] = "My name is Li jilin";
  char a2[] = "Mr Zhang HaoLing is very happy";
  char a3[100] = "";
  char *p1 = a1, *p2 = a2;
  char *p3 = a3;
  int i = 0;
  // 指针写法
  for (; *p2 != '\0';)
  {
    p2++;
    i++;
    if (i >= 3 && i <= 16)
    {
      *p3 = *p2;
      if (i == 16)
      {
        break;
      }
      else
      {
        printf("p3++,*p3=%c\n", *p3);
        p3++;
      }
    }
    // if (i >= 3 && i <= 16)
    // {
    //   *p3 = *p2;
    //   if (i == 16)
    //   {
    //     *p3 = '\0'; // p3表示结束
    //     break;
    //   }
    //   else
    //   {
    //     p3++;
    //   }
    // }
  }
  // p3 = a3; // 指针指回第一个
  // for (; *p3 != '\0'; p3++)
  // {
  //   printf("%c", *p3);
  // }
  // p2 = a2;
  // printf("\n");
  printf("i=%d,a2=%s", i, a2);
  // printf("\n");
  // for (; *p2 != '\0'; p2++)
  // {
  //   printf("%c", *p2);
  // }
  // printf("\n");
}