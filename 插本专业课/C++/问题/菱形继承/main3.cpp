#include <iostream>
using namespace std;

class A
{
public:
  virtual void print()
  {
    std::cout << "This is A's print function." << std::endl;
  }
};
class B : virtual public A
{
public:
  void print()
  {
    std::cout << "This is B's print function." << std::endl;
  }
};
class C : virtual public A
{
public:
  void print()
  {
    std::cout << "This is C's print function." << std::endl;
  }
};

class D : public C, public B
{
  // void print()
  // {
  //   std::cout << "This is D's print function." << std::endl;
  // }
};

int main()
{
  // 写法1
  // D d;
  // A *aPtr = &d;
  // aPtr->print();

  // 写法2
  // A *aPtr = new D();
  // aPtr->print();
  // delete aPtr;
  return 0;
}

// class A
// {
// public:
//   virtual void print()
//   {
//     std::cout << "This is A's print function." << std::endl;
//   }
// };

// // 使用虚继承，确保在后续派生类中只有一份A类的成员
// class B : virtual public A
// {
// public:
//   void print() override
//   {
//     std::cout << "This is B's print function." << std::endl;
//   }
// };

// class C : virtual public A
// {
// public:
//   void print() override
//   {
//     std::cout << "This is C's print function." << std::endl;
//   }
// };

// class D : public C, public B
// {
// };

// int main()
// {
//   A *aPtr = new D();
//   aPtr->print();
//   delete aPtr;
//   return 0;
// }