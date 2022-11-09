#include <stdio.h>
#include <math.h>
#define PI 3.14

int main()
{
  /*
  1.如何区分表达式和表达式语句？C语言为什么要设表达式语句？
  什么时候用表达式，什么时候用表达式语句

  表达式：用C语言运算符将运算对象连接起来的式子。
  表达式语句：由表达式加一个分号
  */

  /*
  2. C语言为什么要把输入输出功能作为函数，而不作为语言的基本部分？

  不把输入输出语句作为C语句的目的是使C语言编译系统简单，因为将语句
  翻译成二进制的指令是在编译阶段完成的，没有输入输出语句可以避免在编译
  阶段处理与硬件相关的问题，使得编译系统建华，同性性强，可移植性好。
   */

  /*
  3.用下面的scanf函数输入数据，使得a=3,b=7,x=8.5,
  y=71.82,c1='A',c2='a'
  */

  // int a, b;
  // float x, y, z;
  // char c1, c2;
  // scanf("a=%d b=%d", &a, &b); // 输入a=20 b=30
  // scanf(" %f %e", &x, &y); // 输入 8.5 71.82
  // scanf(" %c %c", &c1, &c2); // 输入 Aa
  // printf("%c,%c", c1, c2);
  // printf("%.1f,%.2f", x, y);
  // printf("%d,%d", a, b);

  /*
  4.用下面的scanf函数输入数据，使得a=10,b=20,c1='A',c2='a'
  x=1.5,y = -3.75, z=67.8
  */
  // int a, b;
  // float x, y, z;
  // char c1, c2;
  // scanf("%5d%5d%c%c%f%f%*f,%f", &a, &b, &c1, &c2, &x, &y, &z); // 10 20Aa1.5 -3.75 3.1,67.8
  // printf("%d,%d,%c,%c,%.1f,%.2f,%.1f", a, b, c1, c2, x, y, z);

  /*
  5.设圆半径r=1.5 圆柱高h=3，求圆周长，圆面积，圆球表面积，圆球体积，圆柱体积
  圆球表面积S=4πr^2, 体积V=(4/3)πr^3
  */
  // float r, h;
  // float len, area, surfaceArea, ballVolume, cylinderVolume; // 分别为圆周长，圆面积，圆球表面积，圆球体积，圆柱体积变量
  // printf("请输入圆半径和圆柱的高度");
  // scanf("%f,%f", &r, &h);
  // len = PI * 2 * r;
  // area = PI * pow(r, 2);
  // surfaceArea = PI * pow(r, 2) * 4;
  // ballVolume = (4 / 3) * PI * pow(r, 3);
  // cylinderVolume = area * h;
  // printf("圆周长为%.2f\n圆面积为%.2f\n圆球表面积为%.2f\n圆球体积为%.2f\n圆柱体积为%.2f\n", len, area, surfaceArea, ballVolume, cylinderVolume);

  /*
  6. 输入一个华氏温度，要求输出摄制温度，公司为 c=5/9(F-32)
  */

  // float c, F;
  // printf("请输入华氏度");
  // scanf("%f", &F);
  // c = (5.0 / 9.0) * (F - 32);
  // printf("华氏度%.2f转换成摄氏度为%.2f", F, c);

  return 0;
}