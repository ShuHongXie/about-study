#include <iostream>
using namespace std;

class Shape
{
public:
  virtual void draw()
  {
    cout << "shape draw" << endl;
  }
};

class Circle : public Shape
{
public:
  void draw()
  {
    // 绘制圆形的具体代码
    cout << "circle draw" << endl;
  }
};

class Rectangle : public Shape
{
public:
  void draw()
  {
    // 绘制圆形的具体代码
    cout << "Rectangle draw" << endl;
  }
};

int main()
{
  /*

  * 当通过基类的指针或引用调用一个虚函数时，程序会在运行时根据指针或引用所指向（或引用）的实际对象的类型来决定调用哪个版本的函数。例如：
  * 编译器会为每个包含虚函数的类创建一个虚函数表（v - table），虚函数表中存储了类中所有虚函数的地址。
  * 每个类的对象会包含一个指向虚函数表的指针（v - pointer）。当通过基类指针或引用调用虚函数时，
  * 程序会根据对象的 v - pointer 找到对应的 v - table，然后在 v - table 中查找要调用的函数的实际地址。

  */
  Shape *shapePtr;
  Circle circle;
  Rectangle rectangle;
  // 指向圆形对象
  shapePtr = &circle;
  shapePtr->draw(); // 调用Circle::draw()
  // 指向矩形对象
  shapePtr = &rectangle;
  shapePtr->draw(); // 调用Rectangle::draw()
  return 0;
}