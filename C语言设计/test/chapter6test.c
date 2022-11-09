#include <stdio.h>
#include <string.h>

int main()
{
  // 1. 一个班有2个学生的成绩，要求输入这2个学生的成绩，然后哦求出他们的平均成绩。
  // 2. 在上题基础是哪个求出平均成绩最高的课程
  /*
  char *switchSubject(int num);
  float score[2][3];
  float average[2];    // 平均成绩
  float subject[3][2]; // 存储3科成绩
  float maxSubjectScoreIndex = 0;
  float maxSubjectAverage = 0;
  float totalSubjectAverage = 0;
  float subjectAverage = 0;
  float maxScoreNum = 0; // 最高成绩课程
  float maxScore = 0;    // 最高成绩
  float sum[2];          // 成绩总和

  printf("请分别输入学生语文数学英语的成绩，按空格隔开\n");
  for (int i = 0; i < 2; i++)
  {
    sum[i] = 0;
    average[i] = 0;
    for (int j = 0; j < 3; j++)
    {
      scanf("%f,", &score[i][j]);
      subject[j][i] = score[i][j];
    }
  }
  for (int k = 0; k < 2; k++)
  {
    for (int h = 0; h < 3; h++)
    {
      sum[k] += score[k][h];
    }
    average[k] = sum[k] / 3.0;
    printf("学生%d的平均成绩为%.0f\n", k + 1, average[k]);
  }
  for (int a = 0; a < 3; a++)
  {
    totalSubjectAverage = 0;
    for (int b = 0; b < 2; b++)
    {
      totalSubjectAverage += subject[a][b];
      printf("%0.f\n", subject[a][b]);
    }

    if (subjectAverage < totalSubjectAverage)
    {
      subjectAverage = totalSubjectAverage;
      maxSubjectScoreIndex = a;
    }
  }
  maxSubjectAverage = subjectAverage / 2.0;
  printf("其中平均成绩最高的课程为为%s，成绩为%.0f\n", switchSubject(maxSubjectScoreIndex), maxSubjectAverage);
  */

  // 2.将一个数组中的值按逆序重新排放
  /*
  int arr[7] = {1, 2, 3, 4, 5, 6, 7};
  int i;
  for (i = 0; i < 7; i++)
  {
    if (i < 4)
    {
      int j = arr[i];
      arr[i] = arr[6 - i];
      arr[6 - i] = j;
    }
  }
  for (i = 0; i < 7; i++)
  {
    printf("%d", arr[i]);
  }
  */

  /* 3.输出以下图案
  *****
  z*****
  zz*****
  zzz*****
  zzzz*****

  char str[100] = "******";
  char space[100] = "";
  char newStr[100] = "";
  for (int i = 0; i < 5; i++)
  {
    strcat(newStr, space);
    strcat(newStr, str);
    printf("%s\n", newStr);
    newStr[i] = '\0';
    strcat(newStr, " ");
  }
  */

  // 有一行电文，按以下规律翻译成密码 A-Z A-z B-Y b-y C-X c-x
  char upper[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char lower[26] = "abcdefghijklmnopqrstuvwxyz";
  char example[10] = "U";
  for (int i = 0; example[i] != '\0'; i++)
  {
    printf("%d\n", example[i]);
    char str;
    if (example[i] > 64 && example[i] < 91)
    {
      example[i] = 26 - (example[i] - 64);
      printf("%d\n1", 26 - (example[i] - 64));
      printf("%c\n2", example[i]);
    }
    else if (example[i] > 96 && example[i] < 123)
    {
      example[i] = 96 + 26 - example[i] + 64 + 1;
    }
  }
  printf("%s\n", example);
  return 0;
}

char *switchSubject(int num)
{
  switch (num)
  {
  case 0:
    return "语文";
    break;
  case 1:
    return "数学";
    break;
  case 2:
    return "英语";
    break;
  }
}