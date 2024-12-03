/*
编写一个程序，定义抽象基类Shape，在Shape类中定义虚函数area()；由它派生出3个派生类：Circle(圆形)、
Square(正方形)、Rectangle(矩形)。用虚函数分别计算几种图形面积。
1、要求输出结果保留两位小数。
2、要求用基类指针数组，使它每一个元素指向每一个派生类对象。

输入

测试数据的组数 t

第一组测试数据中圆的半径

第一组测测试数据中正方形的边长

第一组测试数据中矩形的长、宽

.......

第 t 组测试数据中圆的半径

第 t 组测测试数据中正方形的边长

第 t 组测试数据中矩形的长、宽


输出

第一组数据中圆的面积

第一组数据中正方形的面积

第一组数据中矩形的面积

......

第 t 组数据中圆的面积

第 t 组数据中正方形的面积

第 t 组数据中矩形的面积

#include <iostream>
#include <iomanip>
using namespace std;

class Shape
{
public:
  virtual void Area() const // 定义的虚函数
  {
  }
};

class Circle : public Shape
{
public:
  double bj;                // 半径
  virtual void Area() const // 定义的虚函数
  {
    cout << fixed << setprecision(2) << bj * bj * 3.14 << endl;
  }
  Circle(double bj1)
  {
    bj = bj1;
  }
};

class Square : public Shape
{
public:
  double bian;
  virtual void Area() const // 定义的虚函数
  {
    cout << fixed << setprecision(2) << bian * bian << endl;
  }
  Square(double bian1)
  {
    bian = bian1;
  }
};

class Rectangle : public Shape
{
public:
  double w;
  double h;
  virtual void Area() const // 定义的虚函数
  {
    cout << fixed << setprecision(2) << w * h << endl;
  }
  Rectangle(double w1, double h1)
  {
    w = w1;
    h = h1;
  }
};

int main()
{
  int count;
  cin >> count;

  for (int i = 0; i < count; i++)
  {
    Shape *shape;
    double bj;
    cin >> bj;
    Circle c1(bj);
    shape = &c1;
    shape->Area();

    double bian;
    cin >> bian;
    Square s1(bian);
    shape = &s1;
    shape->Area();

    double w, h;
    cin >> w >> h;
    Rectangle r1(w, h);
    shape = &r1;
    shape->Area();
  }
  return 0;
}
*/

/*
题目2描述

现在要开发一个系统，实现对多种汽车的收费工作。 汽车基类框架如下所示：

class Vehicle
{
protected:
     string no; //编号
public:
    virtual void display()=0; //应收费用
}
以Vehicle为基类，构建出Car、Truck和Bus三个类。

Car的收费公式为： 载客数*8+重量*2

Truck的收费公式为：重量*5

Bus的收费公式为： 载客数*30

生成上述类并编写主函数，要求主函数中有一个基类指针Vehicle *pv;用来做测试用。

主函数根据输入的信息，相应建立Car,Truck或Bus类对象，对于Car给出载客数和重量，Truck给出重量，Bus给出载客数。假设载客数和重量均为整数。


输入

第一行表示测试次数。从第二行开始，每个测试用例占一行，每行数据意义如下：汽车类型（1为car，2为Truck，3为Bus）、编号、基本信息（Car是载客数和重量，Truck给出重量，Bus给出载客数）。


输出

车的编号、应缴费用

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Vehicle
{
public:
  string no; // 编号
public:
  virtual void display() = 0; // 应收费用
};

class Car : public Vehicle
{
public:
  int zaiNum;
  int weight;
  void display()
  {
    cout << no << " " << zaiNum * 8 + weight * 2 << endl;
  }
};

class Truck : public Vehicle
{
public:
  int weight;
  void display()
  {
    cout << no << " " << weight * 5 << endl;
  }
};

class Bus : public Vehicle
{
public:
  int zaiNum;
  void display()
  {
    cout << no << " " << zaiNum * 30 << endl;
  }
};

int main()
{
  int count;
  cin >> count;
  Vehicle *pv;
  for (int i = 0; i < count; i++)
  {
    int type;
    cin >> type;
    if (type == 1)
    {
      Car *c = new Car;
      cin >> c->no >> c->zaiNum >> c->weight;
      pv = c;
      pv->display();
    }
    else if (type == 2)
    {
      Truck *t = new Truck;
      cin >> t->no >> t->weight;
      pv = t;
      pv->display();
    }
    else
    {
      Bus *b = new Bus;
      cin >> b->no >> b->zaiNum;
      pv = b;
      pv->display();
    }
  }
  return 0;
}

*/

/* 题目3protected保护写法
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Vehicle
{
protected:
  string no; // 编号
public:
  virtual void display() = 0; // 应收费用
};

class Car : public Vehicle
{
public:
  int zaiNum;
  int weight;
  void display()
  {
    cout << no << " " << zaiNum * 8 + weight * 2 << endl;
  }
  void setProperty(string no1, int zaiNum1, int weight1)
  {
    no = no1;
    weight = weight1;
    zaiNum = zaiNum1;
  }
};

class Truck : public Vehicle
{
public:
  int weight;
  void display()
  {
    cout << no << " " << weight * 5 << endl;
  }
};

class Bus : public Vehicle
{
public:
  int zaiNum;
  void display()
  {
    cout << no << " " << zaiNum * 30 << endl;
  }
};

int main()
{
  int count;
  cin >> count;
  Vehicle *pv;
  for (int i = 0; i < count; i++)
  {
    int type;
    cin >> type;
    if (type == 1)
    {
      Car *c = new Car;
      string no;
      int zaiNum, weight;
      cin >> no >> zaiNum >> weight;
      c->setProperty(no, zaiNum, weight);
      pv = c;
      pv->display();
    }
    // else if (type == 2)
    // {
    //   Truck *t = new Truck;
    //   cin >> t->no >> t->weight;
    //   pv = t;
    //   pv->display();
    // }
    // else
    // {
    //   Bus *b = new Bus;
    //   cin >> b->no >> b->zaiNum;
    //   pv = b;
    //   pv->display();
    // }
  }
  return 0;
}
*/

/* 第四题
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class BaseAccount
{
public:
  string name;
  string account;
  double balance;
  double realBalance;
  virtual void deposit(double m)
  {
    balance += m;
    realBalance = balance;
  }
  virtual void withdraw(double m)
  {
    realBalance = balance;
    balance -= m;
    if (balance > 0)
    {
      realBalance = balance;
    }
  };
  virtual void display()
  {
    if (balance < 0)
    {
      cout << "insufficient" << endl;
    }
    cout << name << " " << account << " " << "Balance:" << realBalance << endl;
  }
  void setP(string name1, string account1, double balance1)
  {
    name = name1;
    account = account1;
    realBalance = balance1;
    balance = balance1;
  }
};

class BasePlus : public BaseAccount
{
public:
  static double touziTop;
  double limitSum;
  virtual void withdraw(double m)
  {
    realBalance = balance;
    balance -= m;
    if (balance > 0)
    {
      realBalance = balance;
    }
    else if (balance < 0 && -balance < touziTop)
    {
      realBalance = 0;
    }
  };
  void display()
  {
    if (balance < 0 && -balance >= touziTop)
    {
      cout << "insufficient" << endl;
    }
    cout << name << " " << account << " " << "Balance:" << realBalance << " ";
    if (balance < 0)
    {
      limitSum = -balance > touziTop ? touziTop : touziTop - -balance;
      cout << "limit:" << limitSum << endl;
    }
  }
};

double BasePlus::touziTop = 5000;

int main()
{
  int t;
  cin >> t;
  BaseAccount *ba;
  for (int i = 0; i < t; i++)
  {
    string name, account;
    double balance;
    cin >> name >> account >> balance;
    double c1, c2, q1, q2;
    if (account.substr(0, 2) == "BA")
    {
      // BaseAccount *ba = new BaseAccount;
      ba = new BaseAccount();
      ba->setP(name, account, balance);
      cin >> c1 >> q1 >> c2 >> q2;
      ba->deposit(c1);
      ba->withdraw(q1);
      ba->deposit(c2);
      ba->withdraw(q2);
      ba->display();
    }
    else
    {
      ba = new BasePlus();
      ba->setP(name, account, balance);
      cin >> c1 >> q1 >> c2 >> q2;
      ba->deposit(c1);
      ba->withdraw(q1);
      ba->deposit(c2);
      ba->withdraw(q2);
      ba->display();
    }
  }
  return 0;
}
*/

/*
第五题
#include <iostream>
#include <string>
using namespace std;
class Animal
{
public:
  string name;
  int age;
  void virtual speak()
  {
  }
};
class Tiger : public Animal
{

  void speak()
  {
    cout << "Hello,I am " << name << ",AOOO." << endl;
  }
};
class Dog : public Animal
{
  void speak()
  {
    cout << "Hello,I am " << name << ",WangWang." << endl;
  }
};
class Duck : public Animal
{
  void speak()
  {
    cout << "Hello,I am " << name << ",GAGA." << endl;
  }
};
class Pig : public Animal
{
  void speak()
  {
    cout << "Hello,I am " << name << ",HENGHENG." << endl;
  }
};

int main()
{
  int count;
  cin >> count;
  Animal *p1 = new Animal;
  int age;
  Tiger t;
  Pig p;
  Dog d;
  Duck d1;
  for (int i = 0; i < count; i++)
  {
    string type, name;
    cin >> type >> name >> age;
    if (type == "Tiger")
    {
      p1 = &t;
    }
    else if (type == "Pig")
    {
      p1 = &p;
    }
    else if (type == "Dog")
    {

      p1 = &d;
    }
    else if (type == "Duck")
    {
      p1 = &d1;
    }
    else
    {
      cout << "There is no " << type << " in our Zoo." << endl;
    }
    p1->name = name;
    p1->age = age;
    p1->speak();
  }
  return 0;
}
*/