#include <iostream>
using namespace std;

// c++菱形继承问题
/*
非虚继承产生二义性的原因 在最初的非虚继承部分，类D继承自B和C，而B和C都继承自A。当访问D对象中的num成员时，
编译器不知道应该选择从B路径继承的A::num还是从C路径继承的A::num，所以会产生二义性。例如d.num = 20;
这行代码就会编译报错。 通过使用作用域限定符（如d.B::num = 20;和d.C::num = 30;）可以明确指定访问路径来解决编译报错，
但这种方式并没有真正解决数据冗余的问题，因为实际上在D对象中存在两份A类的数据成员（通过B和C路径各继承一份）。
 虚继承解决二义性的原理 虚继承机制 当使用虚继承（如class VB : virtual public A和class VC : virtual public A）时，
 编译器会保证在最终的派生类（如VD）中只有一份A类的数据成员和函数成员。
  在虚继承的实现过程中，编译器会在对象内存布局中添加额外的指针（称为虚基类指针）来管理虚基类（这里是A类）的数据成员和函数成员的访问。
  这些指针指向一个共享的虚基类子对象，使得从不同路径继承的虚基类部分在内存中只有一份副本。
  访问成员的变化 在VD类的对象vd中，对于num成员的访问不再有二义性。因为只有一份A类的num成员存在于VD对象的内存布局中，所以vd.num = 40;
  这行代码能够正确地访问和修改这个唯一的num成员，不会出现编译器无法确定访问路径的情况。并且，通过这种方式也解决了数据冗余的问题，提高了内存使用效率。
 */

// 定义基类A
class A
{
public:
  int num;
  A(int n) : num(n) {}
};

// 类B继承自类A（非虚继承情况）
class B : public A
{
public:
  B(int n) : A(n) {}
};

// 类C继承自类A（非虚继承情况）
class C : public A
{
public:
  C(int n) : A(n) {}
};

// 类D继承自类B和类C，形成菱形继承结构（非虚继承时会有问题）
class D : public B, public C
{
public:
  D(int n) : B(n), C(n) {}
};

int main()
{
  // 创建D类的对象，会出现二义性问题
  // D d(10);
  // 下面这行代码编译会报错，因为不清楚访问的是B路径继承的num还是C路径继承的num
  // d.num = 20;

  // 通过作用域限定符来指定访问路径可以解决编译报错，但数据冗余问题依然存在
  D d(10);
  d.B::num = 20;
  d.C::num = 30;
  cout << "通过B路径访问num: " << d.B::num << endl;
  cout << "通过C路径访问num: " << d.C::num << endl;

  // 下面使用虚继承来解决菱形继承的问题

  // 重新定义类B，采用虚继承自类A
  class VB : virtual public A
  {
  public:
    VB(int n) : A(n) {}
  };

  // 重新定义类C，采用虚继承自类A
  class VC : virtual public A
  {
  public:
    VC(int n) : A(n) {}
  };

  // 重新定义类D，继承自虚继承后的类B和类C
  class VD : public VB, public VC
  {
  public:
    // 上面两个采用虚继承，这里需要增加一个对A类的构造传值，不是虚继承不用
    VD(int n) : VB(n), VC(n), A(n) {}
  };

  VD vd(10);
  vd.num = 40; // 此时不会有二义性问题，也不存在数据冗余，只有一份num
  cout << "通过虚继承后访问num: " << vd.num << endl;

  return 0;
}