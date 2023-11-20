#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    ofstream out("out.txt", ios::out); //w
    out << "ABC\0\x61\x62\x63\n" << endl;
    out.close();

    return 0;
}

