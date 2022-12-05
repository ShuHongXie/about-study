#include <stdio.h>

void changes(arr[])
{
  arr[2] = 10;
}

int main()
{
  int arr[3] = {1, 2, 3};
  changes(arr);
  printf("%d", arr[2]);
  return 0;
}