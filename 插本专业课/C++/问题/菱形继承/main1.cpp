#include <iostream>
using namespace std;

class A
{
public:
  void print()
  {
    std::cout << "This is A's print function." << std::endl;
  }
};
class B
{
public:
  void print()
  {
    std::cout << "This is B's print function." << std::endl;
  }
};
class C : public A, public B
{
  // 没有新的成员定义，只是继承了A和B
};
int main()
{
  C c;
  // c.print(); // 这行代码会产生二义性错误
  // 正确的调用方式可以是通过作用域限定符来明确调用哪个基类的函数
  // c.A::print();
  // c.B::print();

    return 0;
}