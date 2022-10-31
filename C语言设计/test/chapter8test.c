#include <stdio.h>

// 指针应用练习-整形改变 -------------------start
// int main()
// {
//   void exchange(int *s1, int *s2);
//   int a, b;
//   scanf("%d,%d", &a, &b);
//   int *p1 = &a;
//   int *p2 = &b;
//   exchange(p1, p2);
//   printf("%d,%d\n", *p1, *p2);
// }

// 整形情况下值传递 改变指针变量对应变量的值可以
// void exchange(int *s1, int *s2)
// {
//   printf("%d,%d\n", *s1, *s2);
//   if (*s1 < *s2)
//   {
//     int temp = *s1;
//     *s1 = *s2;
//     *s2 = temp;
//   }
// }

// 整形情况下值传递 改变指针变量对应变量地址 不行
// void exchange(int *s1, int *s2)
// {

//   if (*s1 < *s2)
//   {
//     int *temp = s1;
//     s1 = s2;
//     s2 = temp;
//   }
//   printf("%d,%d\n", *s1, *s2);
// }

// 指针应用练习-整形改变 -------------------end

// 指针应用练习-数组改变 -------------------start
// 数组颠倒
// int main()
// {
//   void exchange(int *arr, int len);
//   int i, arr[10] = {3, 7, 9, 11, 0, 6, 7, 5, 4, 2};
//   for (i = 0; i < 10; i++)
//   {
//     printf("%d", arr[i]);
//   }
//   printf("\n");
//   exchange(arr, 10);
//   for (i = 0; i < 10; i++)
//   {
//     printf("%d", arr[i]);
//   }
//   printf("\n");
// }

// 值代换
// void exchange(int arr[], int len)
// {
//   int num = (len - 1) / 2,
//       i, j, k;
//   // printf("%d\n", len);
//   for (i = 0; i < num; i++)
//   {
//     k = len - 1 - i;
//     j = arr[i];
//     arr[i] = arr[k];
//     arr[k] = j;
//     // printf("%d,%d,%d\n", j, arr[i], arr[len - 1]);
//   }
// }

// 指针法
// void exchange(int *arr, int len)
// {
//   int num = (len - 1) / 2, temp;
//   int *i = arr;         // 指向arr[0]
//   int *p = i + num;     // 指向arr[4]
//   int *l = i + len - 1; // 指向arr[9]
//   for (; i < p; l--, i++)
//   {
//     temp = *l;
//     *l = *i;
//     *i = temp;
//   }
// }
// 指针应用练习-数组改变 -------------------end

// 指针应用练习-字符复制1 -------------------start
// int main()
// {
//   char a[] = "i am a boy.", b[20];
//   char *p1 = a, *p2 = b;
//   // 值表示
//   // for (int i = 0; *(a + i) != '\0'; i++)
//   // {
//   //   *(b + i) = *(a + i);
//   //   printf("%c\n", *(a + i));
//   // }
//   // 指针表示
//   for (; *p1 != '\0'; p1++, p2++)
//   {
//     *p2 = *p1;
//     // printf("%c", *p2);
//   }
//   *p2 = '\0';
//   for (int i = 0; b[i] != '\0'; i++)
//   {
//     printf("%c", b[i]);
//   }
//   printf("\n");
// }
// 指针应用练习-字符复制2= -------------------end

// 有两个字符串，字符串a为I am a teacher，字符串b的内容为you are a student
// 要求把字符串b连接到字符串a的后面，即字符串a的内容为I am a teacher。You are a student
int main()
{
  void link_string(char *arr1, char *arr2);
  char a[40] = "I am a teacher.";
  char b[] = "you are a student";
  char *p1 = a, *p2 = b;
  link_string(p1, p2);
  printf("%s", a);
  return 0;
}

void link_string(char *arr1, char *arr2)
{
  int i;
  for (i = 0; *arr1 != '\0'; i++)
  {
    arr1++;
  }
  for (; *arr2 != '\0'; arr1++, arr2++)
  {
    *arr1 = *arr2;
  }
  *arr1 = '\0';
}