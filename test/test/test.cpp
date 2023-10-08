#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ����Ƿ���ڴ�СΪ m �Ķ�����
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

// ����Ƿ���ڴ�СΪ n ����
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
    int R = 2; // ��ʼ���Ƶ� Ramsey ��

    while (true) {
        vector<vector<int>> graph(R, vector<int>(R, 1)); // ����һ����ȫͼ

        // ����Ƿ���ڴ�СΪ m �Ķ�����
        if (!hasIndependentSet(graph, m)) {
            return R;
        }

        // ����Ƿ���ڴ�СΪ n ����
        if (!hasClique(graph, n)) {
            return R;
        }

        R++; // ���� Ramsey ���Ĺ���ֵ
    }
}

int main() {
    int m = 3; // ��Ҫ����� Ramsey ���ĵ�һ������
    int n = 3; // ��Ҫ����� Ramsey ���ĵڶ�������
    int result = calculateRamseyNumber(m, n);
    cout << "R(" << m << ", " << n << ") = " << result << endl;
    return 0;
}
