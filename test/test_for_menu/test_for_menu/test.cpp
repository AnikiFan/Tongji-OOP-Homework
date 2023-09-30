#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

int get_next_num(const bool new_seed = false, const unsigned int seed = 0)
{
    if (new_seed)
        srand(seed);

    return rand() % 10;
}

int main()
{
    int i;

    /* 产生10个随机数（以当前时间为种子） */
    cout << get_next_num(true, (unsigned int)time(0)) << ' ';
    for (i = 1; i < 10; i++)
        cout << get_next_num() << ' ';
    cout << endl;

    Sleep(1000);//延时1秒，保证下一组time(0)不同

    /* 产生10个随机数（以当前时间为种子） */
    cout << get_next_num(true, (unsigned int)time(0)) << ' ';
    for (i = 1; i < 10; i++)
        cout << get_next_num() << ' ';
    cout << endl;

    /* 产生10个随机数（以12345为种子） */
    cout << get_next_num(true, 12345) << ' ';
    for (i = 1; i < 10; i++)
        cout << get_next_num() << ' ';
    cout << endl;

    /* 产生10个随机数（以12345为种子）- 和第三组的10个一致 - 说明：只要种子不变，伪随机数序列就不变 */
    cout << get_next_num(true, 12345) << ' ';
    for (i = 1; i < 10; i++)
        cout << get_next_num() << ' ';
    cout << endl;

    return 0;
}
