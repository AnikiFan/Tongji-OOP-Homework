
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;


/********************************/
/*     以下是你需要提交的代码     */
/********************************/
#include<map>
class Solution {
public:
	int solve(std::vector<vector<std::string>>& old_chart, std::vector<std::vector<std::string>>& new_chart) {
		// 这里填写你的代码
		map<string, bool> flag;
		map<string, string>old_map;
		map<string, string>new_map;
		for (int i = 0; i < old_chart.size(); i++)
			for (int j = 0; j < old_chart[0].size(); j++) {
				old_map[old_chart[i][j]] = new_chart[i][j];
				new_map[new_chart[i][j]] = old_chart[i][j];
				flag[old_chart[i][j]] = 0;
			}
		int sum = 0;
		for (int i = 0; i < old_chart.size(); i++)
			for (int j = 0; j < old_chart[0].size(); j++) {
				if (old_chart[i][j] == new_chart[i][j]) {
					flag[old_chart[i][j]] = 1;
					continue;
				}
				if (flag[old_chart[i][j]])
					continue;
				string src = old_chart[i][j], now =old_map[src];
				flag[src] = 1;
				flag[now] = 1;
				while (now != src) {
					sum++;
					now = old_map[now];
					flag[now] = 1;
				}
			}
		return sum;
	}
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<std::string>> old_chart(n, std::vector<std::string>(m));
	std::vector<std::vector<std::string>> new_chart(n, std::vector<std::string>(m));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cin >> old_chart[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cin >> new_chart[i][j];
		}
	}

	Solution s;
	std::cout << s.solve(old_chart, new_chart) << std::endl;
	return true;
}
