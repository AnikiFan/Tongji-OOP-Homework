#include <iostream>
using namespace std;
class A {
private:
    char* s;
public:
    int a;
    A() { s = new char[20]; }
    ~A() {
        cout << "A析构" << endl;
        delete s;
    }
};
class B :public A {
public:
    int b;
    ~B() { cout << "B析构" << endl; }
};
int main()
{
    B b;
    b.a = 15;
    A a1(b);   //复制构造
    A a2;
    a2 = b;    //赋值
}
