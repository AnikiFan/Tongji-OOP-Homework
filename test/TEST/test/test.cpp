#include<iostream>
using namespace std;
class base {
public:
	base() {
		cout << "make a base" << endl;
		a = 1;
	}
	virtual void display(int a) {
		cout << "this is base speaking" << endl;
	}
	int a;
};
class child :public base{
public:
	child() {
		cout << "make a child" << endl;
		a = 10;
	}
	void display() {
		cout << "this is child speaking" << endl;
	}
	int a;
};
int main()
{
	base test_base;
	child test_child;
	base* base_p=NULL;
	child* child_p=NULL;
	base_p = &test_base;
	base_p->display(10);
	cout << base_p->a << endl;
	base_p = &test_child;
	base_p->display();
	cout << test_child.base::a<<endl;
	return 0;
}
