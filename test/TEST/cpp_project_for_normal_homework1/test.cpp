#include<iostream>
using namespace std;
#define N 6 
int Map[N][N] = {//下标为0的元素为冗余
	{0,0,0,0,0,0},
	{0,0,1,1,0,1},
	{0,1,0,1,0,1},
	{0,1,1,0,1,1},
	{0,0,0,1,0,1},
	{0,1,1,1,1,0}
};
void DFS(string path, int now)
{
	for (int i = 1; i < N; i++)
		if (Map[now][i]) {
			path.push_back(i + '0');
			if (path.length() == 9) {
				cout << path << endl;
				return;
			}
			Map[now][i] = 0;
			Map[i][now] = 0;
			DFS(path, i);
			path.pop_back();
			Map[now][i] = 1;
			Map[i][now] = 1;
		}
	return;
}
int main()
{
	DFS("1", 1);
	return 0;
}

