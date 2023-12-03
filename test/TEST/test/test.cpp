#include<iostream>
using namespace std;
#include<set>

int main()
{
	set<int,greater<int>>s;
	s.insert(2);
	s.insert(1);
	s.insert(3);
	set<int,greater<int>>::iterator it = s.begin();
	while (it != s.end())
		cout << *it++ << endl;
	return 0;
}
