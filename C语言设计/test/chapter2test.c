#include <stdio.h>
#include <math.h>

int main()
{
  // 2.1 假如我国过敏生产总值的年增长率为10%，计算10年后我国过敏生产总值和现在
  // 相比增长多少百分比

  // float r = 0.1;
  // double p = pow((1 + r), 10);
  // printf("%.2lf%%\n", p);

  // 2.3 将China翻译成密码，规律是由原来字幕后面的第4个字幕代替原来的字母。
  // 例如：字母A后面第4个字母是E，用E代替A，因此China应翻译为Glmre

  // char c1 = 'C';
  // char c2 = 'h';
  // char c3 = 'i';
  // char c4 = 'n';
  // char c5 = 'a';
  // c1 += 4;
  // c2 += 4;
  // c3 += 4;
  // c4 += 4;
  // c5 += 4;
  // printf("%c%c%c%c%c", c1, c2, c3, c4, c5);

  // 2.4 例3能否改成如下：可以
  int c1 = 97, c2 = 98;
  printf("%c %c\n", c1, c2); // a b
  printf("%d %d\n", c1, c2); // 97 98
  // 如果将程序第4，5行改为 c1=197 c2=198 会输出什么信息？为什么？
  // 会输出 ?? 因为字符存储是通过转换成ASCII码存储到存储单元中的，实际访问的是ASCII所对应的地址
  // 但是编号为197,198的号码不存在 ASCII最高支持到编号127

  return 0;
}