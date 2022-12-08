#include <stdio.h>
#include <stdlib.h>
int main()
{

  char arr[] = " sadsa213";
  char news[] = "";
  // char *news;
  int j = 0;
  for (int i = 0; arr[i] != '\0'; i++)
  {
    if (arr[i] == ' ' || arr[i] > '0' && arr[i] < '9')
    {
      news[j] = arr[i];
      j++;
    }
  }
  printf("%s\n", news);
  return 0;
}