#include <stdio.h>
#include <stdlib.h>

// 读入文件
// int main()
// {
//   FILE *fp;
//   char ch, filename[10];
//   printf("请输入所用的文件名：");
//   scanf("%s", filename);
//   if ((fp = fopen(filename, "w")) == NULL)
//   {
//     printf("无法打开文件\n");
//     exit(0); // 终止程序
//   }
//   ch = getchar();
//   printf("请输入一个准备存储到磁盘的字符串，(以#结束)：");
//   // ch = getchar();
//   while (ch != '#')
//   {
//     fputc(ch, fp);
//     putchar(ch);
//     ch = getchar();
//   }
//   fclose(fp);
//   putchar(10);
//   return 0;
// }

int main()
{
  FILE *in, *out;
  char ch, infile[10], outfile[10];
  printf("请输入读入文件的名字");
  scanf("%s", infile);
  printf("请输入输出文件的名字");
  scanf("%s", outfile);
  if ((in = fopen(infile, "r")) == NULL)
  {
    printf("无法打开此文件\n");
    exit(0);
  }
  if ((out = fopen(outfile, "w")) == NULL)
  {
    printf("无法打开此文件\n");
    exit(0);
  }
  ch = fgetc(in);
  while (!feof(in))
  {
    fputc(ch, out);
    putchar(ch);
    ch = fgetc(in);
  };
  putchar(10);
  fclose(in);
  fclose(out);
  return 0;
}