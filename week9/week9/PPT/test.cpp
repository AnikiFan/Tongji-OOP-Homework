/* 2254298 ´óÊı¾İ ·¶äì */
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    ofstream out("out.txt", ios::out);
    out << "hello" << endl;
    out.close();

    ifstream in("out.txt", ios::in | ios::binary);
    while (!in.eof())
        cout << in.get() << ' ';
    cout << endl;
    in.close();
    return 0;
}


