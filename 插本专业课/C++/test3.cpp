// 面向对象10-15章重要实例

#include <iostream>

using namespace std;

/*
普通类
class Tdate
{
public:
  int x;
  void set(int y, int m, int d)
  {
    this->year = y;
    this->month = m;
    this->day = d;
  }
  void print();

private:
  int year, month, day;
};

void Tdate::print()
{
  cout << year << "/" << month << "/" << day << endl;
}

void print()
{
  cout << "call print" << endl;
}

int main()
{
  Tdate a;
  a.x = 90;
  cout << "x" << a.x << endl;

  a.set(1998, 6, 6);
  a.print();
  print();
}
*/

/*
同名类名覆盖变量，使用变量通过::作用域符号知名
变量覆盖同名类名，使用类名class强行指明
int s = 0;
int main()
{
  class s
  {
  private:
    int t, m, n;
  };
  class s a;
  ::s = 3;
  cout << ::s << endl;
  return 0;
}
*/

/*
结构体方法调用
struct stud
{
  string name;
  void func()
  {
    cout << "call function" << endl;
  }
} s1;

int  main()
{
  s1.func();
  return 0;
}
*/

/*
构造函数和构造函数重载
class Tdate
{
public:
  // Tdate(); // 无参数构造函数
  // Tdate(int d);
  Tdate(int m = 3, int d = 5) // 默认参数的构造函数不能写在外部Tdate::Tdate()
  {
    year = 1900;
    month = m;
    day = d;
  }
  void print()
  {
    cout << year << "/" << month << "/" << day << endl;
  }

private:
  int year, month, day;
};
// Tdate::Tdate()
// {
//   year = 1900;
//   month = 1;
//   day = 1;
// }

// Tdate::Tdate(int d)
// {
//   year = 1900;
//   month = 1;
//   day = d;
// }
// Tdate::Tdate(int m = 3, int d = 5)
// {
//   year = 1900;
//   month = m;
//   day = d;
// }
int main()
{
  Tdate d1;
  d1.print();
  Tdate d2(10);
  d2.print();
  Tdate d3(2, 12);
  d3.print();
}
*/

/*
拷贝构造函数

class myclass
{
private:
  int x, y;

public:
  myclass(int i, int j)
  {
    cout << "create object" << endl;
    x = i;
    y = j;
  }
  myclass()
  {
    cout << "调用了构造函数" << endl;
  }
  // 拷贝构造函数
  myclass(const myclass &obj)
  {
    cout << "create copy fun" << endl;
    x = obj.x;
    y = obj.y;
  }
  void disp()
  {
    cout << "x=" << x << " y=" << y << endl;
  }
};

int main()
{
  // myclass a;
  myclass a(4, 5);
  myclass b(a);  // 激活拷贝构造函数方式1
  myclass c = a; // 激活拷贝构造函数方式2
  b.disp();
  c.disp();
}
*/

/*
构造函数初始化列表x(h), y(v)
如果数据成员是const或引用的话，必需采用初始化列表将其初始化。
const和引用，只能初始化，不能赋值。

#include <iostream>
class Point
{
private:
  float x, y; // 点的坐标
  // const int ci;
  // int &ri;

public:
  // 构造函数
  Point(float h, float v) : x(h), y(v) {}
  // 错误写法
  Point(int a)
  {
    ci = a;
    ri = a;
  }

  // 正确写法
  // Point(int a) : ci(a), ri(a) {}

  // 析构函数
  ~Point()
  {
    cout << "deconstructor" << endl;
  }
  float GetX(void); // 取X坐标
  float GetY(void); // 取Y坐标
  void Draw(void);  // 在(x,y)处画点
};
float Point::GetX(void)
{
  return x; // 取X坐标
}
float Point::GetY(void)
{
  return y; // 取Y坐标
}
void Point::Draw(void) // 在(x,y)处画点
{
  cout << "(" << x << "," << y << ")" << endl;
}
int main()
{
  Point p(4, 5);
  p.Draw();
}

 */

/*
复合对象：一个对象里面初始化另外一个对象

class CDate
{
private:
  int year, month, day;

public:
  CDate(int y, int m, int d)
  {
    year = y, month = m, day = d;
  }
  // CDate() {}
  // 这种方法需要有一个无参的构造函数
  void setDate(int y, int m, int d)
  {
    year = y, month = m, day = d;
  }
};
class CStudent
{
private:
  char *p_name;
  CDate birthday;

public:
  CStudent(char *p_name_val, int y, int m, int d)
  {
    p_name = new char[strlen(p_name_val) + 1];
    strcpy(p_name, p_name_val);
    birthday.setDate(y, m, d);
    // 调用setDate对子对象birthday始化
  }
  ~CStudent()
  {
    delete[] p_name;
  }
}
*/

/*
拷贝构造函数默认调用

class CDate
{
private:
  int year, month, day;
  char *p_day_name;

public:
  CDate(int y, int m, int d, char *p_day_val) {}
  CDate(const CDate &r)
  {
    cout << "调用--------" << endl;
    year = r.year;
    month = r.month;
    day = r.day;
    p_day_name = new char[strlen(r.p_day_name) + 1];
    strcpy(p_day_name, r.p_day_name);
  }
  ~CDate()
  {
    delete[] p_day_name;
  };
};
int main()
{
  CDate day(1949, 10, 1, "National day");
  CDate day1 = day, day2(day1);
}
*/

/*
浅拷贝和深拷贝的区别
1  在未定义拷贝构造函数的情况下，系统会调用默认的拷贝函数——即浅拷贝（不用自己构造），
它能够完成成员的简单的值的拷贝一一复制。当数据成员中没有指针时，浅拷贝是可行的；
但当数据成员中有指针时，如果采用简单的浅拷贝，则两类中的两个指针将指向同一个地址（同一个堆区），
当对象快结束时，会调用两次析构函数（析构函数也无需自己构造，但想要知道析构函数的工作可以自己构造析构函数用输出来记录），
而导致指针悬挂现象，所以，此时，必须采用深拷贝。
2 深拷贝与浅拷贝的区别就在于深拷贝会在堆内存中另外申请空间来储存数据（新的堆区空间进行拷贝），
从而也就解决了指针悬挂的问题。简而言之，当数据成员中有指针时，必须要用深拷贝。


#include <iostream>

using namespace std;
class Person
{
public:
  Person()
  {
  }
  // 初始化属性
  Person(const char *name, int age)
  {
    Name = (char *)malloc(strlen(name) + 1);
  }
  // 拷贝构造 系统会提供默认拷贝构造，而且是简单的值的拷贝即浅拷贝
  // 增加拷贝构造函数，现在变成了深拷贝
  Person(const Person &p)
  {
    Age = p.Age;
    Name = (char *)malloc(strlen(p.Name) + 1);
    strcpy(Name, p.Name);
  }
  // 析构调用
  ~Person()
  {
    cout << "析构函数的调用" << endl;
    if (Name != NULL)
    {
      free(Name);
      Name = NULL;
    }
  }

  // 姓名
  char *Name;
  // 年龄
  int Age;
};
void test01()
{
  Person p1("光头强", 10);
  Person p2(p1); // 调用拷贝构造
  p1.Age = 300;
  p2.Age = 100;
  cout << "p1的年龄:" << p1.Age << endl;
  cout << "p2的年龄:" << p2.Age << endl;
};

int main(void)
{
  test01();
  system("pause");
  return 0;
}
*/

/*
静态数据成员，共享于所有对象


class Box
{
public:
  // 不加inline无法初始化
  // static int height;
  // 初始化方式1
  inline static int height = 100;
  // 把height定义为静态的数据成员
  int width;
  int length;
  int volume();
  // 静态成员函数
  static void printBoxHeight()
  {
    cout << "Static Height Value: " << height << endl;
  }
};

// 初始化方式2
// int Box::height = 100;

int main()
{
  Box::height = 1000;
  Box::printBoxHeight();

  Box b1;
  b1.height = 2000;
  Box::printBoxHeight();
}
 */

/*
  友元函数没有this，只能通过传入对象来获取this

class Time
{
public:
  Time(int, int, int);
  friend void display(Time &);

  // 声明display为Time类的友元函数
private: // 以下数据是私有数据成员
  int hour, minute, sec;
};

Time::Time(int h, int m, int s)
{
  hour = h;
  minute = m;
  sec = s;
}
void display(Time &t)
// 友元函数
{
  cout << t.hour << ":" << t.minute << ":" << t.sec << endl;
}
int main()
{
  Time t1(10, 13, 56);
  display(t1);
  // 调用display函数，实参t1是Time类对象
}

*/

/*
友元函数的先后顺序问题，如果需要调用另外一个类，那另外一个类
必须提前定义

class A; // 这个不能去掉，不然类A相当于没定义，B类的set_show会拿不到A
class B
{
public:
  void set_show(int x, A &a);
  // 该函数是类A的友元函数
};
class A
{
public:
  friend void B::set_show(int x, A &a);
  // 该函数是友元成员函数的声明
private:
  int data;
  void show()
  {
    cout << data << endl;
  }
};
void B::set_show(int x, A &a)
// 只有在定义类A后才能定义该函数，
// 毕竟，它被设为友元是为了访问类A的成员
{
  a.data = x;
  cout << a.data << endl;
}
int main(void)
{
  class A a;
  class B b;
  b.set_show(1, a);
  return 0;
}

 */