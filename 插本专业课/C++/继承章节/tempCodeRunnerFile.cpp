#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
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
    if (balance < 0)
    {
    }
    else
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
  // 取款
  void withdraw(double m)
  {
    realBalance = balance;
    balance -= m;
    if (balance < 0)
    {

      // cout << "limit:" << (abs(balance) > touziTop ? touziTop : touziTop - abs(balance)) << endl;
    }
    else
    {
      realBalance = abs(balance);
    }
  };
  void display()
  {
    if (balance < 0 && abs(balance) > touziTop)
    {
      cout << "insufficient" << endl;
    }
    cout << name << " " << account << " " << "Balance:" << realBalance << endl;
    if (balance < 0)
    {
      cout << "limit:" << (abs(balance) > touziTop ? touziTop : touziTop - abs(balance)) << endl;
    }
  }
};

double BasePlus::touziTop = 5000;

int main()
{
  int t;
  cin >> t;
  for (int i = 0; i < t; i++)
  {
    string name, account;
    double balance;
    cin >> name >> account >> balance;
    double c1, c2, q1, q2;
    if (account.substr(0, 2) == "BA")
    {
      BaseAccount *ba = new BaseAccount;
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
      BasePlus *bs = new BasePlus;
      bs->setP(name, account, balance);
      cin >> c1 >> q1 >> c2 >> q2;
      bs->deposit(c1);
      bs->withdraw(q1);
      bs->deposit(c2);
      bs->withdraw(q2);
      bs->display();
    }
  }
  return 0;
}