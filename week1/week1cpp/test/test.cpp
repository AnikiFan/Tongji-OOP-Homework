#include<iomanip>
#include<iostream>
using namespace std;
int main()
{
    int a;
    char text[1000];
    cin >> a;
    cout << a<<endl;
    cout << cin.rdstate();
    cin.clear();
    cin >> text;
    cout << text;
    cout << cin.rdstate();
    return 0;
}
