#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 检查是否存在大小为 m 的独立集
bool hasIndependentSet(vector<vector<int>>& graph, int m) {
    int n = graph.size();
    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) {
        vertices[i] = i;
    }

    do {
        bool isIndependent = true;
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                if (graph[vertices[i]][vertices[j]] == 1) {
                    isIndependent = false;
                    break;
                }
            }
            if (!isIndependent) {
                break;
            }
        }
        if (isIndependent) {
            return true;
        }
    } while (next_combination(vertices.begin(), vertices.begin() + m, vertices.end()));

    return false;
}

// 检查是否存在大小为 n 的团
bool hasClique(vector<vector<int>>& graph, int n) {
    int size = graph.size();
    vector<int> vertices(size);
    for (int i = 0; i < size; ++i) {
        vertices[i] = i;
    }

    do {
        bool isClique = true;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (graph[vertices[i]][vertices[j]] == 0) {
                    isClique = false;
                    break;
                }
            }
            if (!isClique) {
                break;
            }
        }
        if (isClique) {
            return true;
        }
    } while (next_combination(vertices.begin(), vertices.begin() + n, vertices.end()));

    return false;
}

int calculateRamseyNumber(int m, int n) {
    int R = 2; // 初始估计的 Ramsey 数

    while (true) {
        vector<vector<int>> graph(R, vector<int>(R, 1)); // 创建一个完全图

        // 检查是否存在大小为 m 的独立集
        if (!hasIndependentSet(graph, m)) {
            return R;
        }

        // 检查是否存在大小为 n 的团
        if (!hasClique(graph, n)) {
            return R;
        }

        R++; // 增加 Ramsey 数的估计值
    }
}

int main() {
    int m = 3; // 想要计算的 Ramsey 数的第一个参数
    int n = 3; // 想要计算的 Ramsey 数的第二个参数
    int result = calculateRamseyNumber(m, n);
    cout << "R(" << m << ", " << n << ") = " << result << endl;
    return 0;
}
