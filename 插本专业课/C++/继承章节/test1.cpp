
/*
继承

#include <iostream>
using namespace std;
class Base
{
private:
  int b_number;

public:
  Base() {}
  Base(int i) : b_number(i) {}
  int get_number()
  {
    return b_number;
  }
  void print()
  {
    cout << b_number << endl;
  }
};
class Derived : public Base
{
private:
  int d_number;

public:

  Derived(int i, int j)
      : Base(i), d_number(j) {};

  void print()
  {
    cout << get_number() << " ";

    cout << d_number << endl;
  }
};
int main()
{
  Base a(2);
  Derived b(3, 4);
  cout << "a is ";
  a.print();


  cout << "b is ";
  b.print();


  cout << "base part of b is";
  b.Base::print();


  return 0;
}
*/

/*
#include <iostream>
using namespace std;

class Base
{
public:
  int i, j, x_temp;
  Base(int i1, int j1) : i(i1), j(j1)
  {
  }
};

class Derived : public Base
{
public:
  Derived(int i1, int j1) : Base(i1, j1)
  {
  }
};

int main()
{
  int i, j;
  cin >> i >> j;
  Base b(i, j);
  Derived d(i, j);
  b = d;
  cout << b.i << endl;
  return 0;
}
*/

/*
#include <iostream>
using namespace std;
class B0 // 基类B0声明
{
public:
  void display()
  {
    cout << "B0::display()" << endl;
    // 公有成员函数
  }
};
class B1 : public B0
{
public:
  void display()
  {
    cout << "B1::display()" << endl;
  }
};
class B2 : public B1
{
public:
  void display()
  {
    cout << "B2::display()" << endl;
  }
};

void fun(B0 *ptr)
{
  ptr->display(); // “对象指针->成员名”
}
int main() // 主函数
{
  B0 b0;   // 声明B0类对象
  B1 b1;   // 声明B1类对象
  B2 b2;   // 声明D1类对象
  B0 *p;   // 声明B0类指针
  p = &b0; // B0类指针指向B0类对象
  fun(p);
  p = &b1; // B0类指针指向B1类对象
  fun(p);
  p = &b2; // B0类指针指向B2类对象
  fun(p);
  return 0;
}
*/

#include <iostream>
using namespace std;

class Base
{
public:
  virtual void print()
  {
    std::cout << "This is the print function of Base class." << std::endl;
  }
};

class Derived : public Base
{
public:
  void print()
  {
    std::cout << "This is the print function of Derived class." << std::endl;
  }
};

int main()
{
  Derived d;
  Base ptr = d;
  ptr.print();
  return 0;
}