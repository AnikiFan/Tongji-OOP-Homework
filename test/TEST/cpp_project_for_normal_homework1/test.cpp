//邻接矩阵实现有权无向联通图最小代价生成树查找
#include<iostream>
#include<queue>
#include<set>
#include<vector>
#define OK 1
#define INFINITY 10000
#define MAXN 100
using namespace std;
typedef struct {
	int Mat[MAXN][MAXN];
	int VecN;
	int ArcN;
}Graph;
typedef int Status;
typedef struct {
	int pos;
	int weight;
	int in;
}NearVec;
typedef struct {
	int a;
	int b;
	int w;
}edge;
Status Init_Graph(Graph& G)
{
	cout << "please type VecN and ArcN" << endl;
	cin >> G.VecN >> G.ArcN;
	for (int i = 0; i < G.VecN; i++)
		for (int j = 0; j < G.VecN; j++)
			G.Mat[i][j] = INFINITY;
	int a, b, w;
	for (int i = 0; i < G.ArcN; i++) {
		cin >> a >> b >> w;
		G.Mat[a][b] = w;
		G.Mat[b][a] = w;
	}
	return OK;
}
void print_tree(NearVec* NearVertices, int n)
{
	for (int i = 0; i < n; i++)
		if (NearVertices[i].pos != -1)
			cout << "(" << i << "," << NearVertices[i].pos << "):" << NearVertices[i].weight << endl;
	return;
}
void Prim(Graph G, int first)
{
	NearVec* NearVertices = new NearVec[G.VecN];
	if (!NearVertices) {
		cout << "OVERFLOW" << endl;
		return;
	}
	cout << "Prim Algorithm" << endl;
	int to_add = first;
	for (int i = 0; i < G.VecN; i++) {
		NearVertices[i].pos = -1;
		NearVertices[i].weight = INFINITY;
		NearVertices[i].in = 0;
	}
	NearVertices[to_add].in = 1;
	while (1) {
		int temp_w = INFINITY;
		for (int i = 0; i < G.VecN; i++)
			if ((G.Mat[to_add][i] != INFINITY) && (!NearVertices[i].in) && (G.Mat[to_add][i] < NearVertices[i].weight)) {//i结点与新加入到树中的结点之间有边，且i结点不在树中，同时边的权重小于目前i中所存储的权重
				NearVertices[i].pos = to_add;
				NearVertices[i].weight = G.Mat[to_add][i];
			}
		int pre = to_add;
		for (int i = 0; i < G.VecN; i++)
			if (NearVertices[i].weight < temp_w && !NearVertices[i].in) {
				temp_w = NearVertices[i].weight;
				to_add = i;
			}
		NearVertices[to_add].in = 1;
		if (temp_w == INFINITY)
			break;
	}
	print_tree(NearVertices, G.VecN);
	return;
}
void Kruskal(Graph G)
{
	cout << "Kruskal Algorithm" << endl;
	std::set<int>S;
	std::queue<edge>Q;
	std::vector<edge>MCT;
	int count = G.ArcN;
	edge min;
	int Flag[MAXN][MAXN] = { 0 };
	while (count) {
		min = { -1,-1,INFINITY };
		for (int i = 0; i < G.VecN; i++)
			for (int j = i + 1; j < G.VecN; j++)
				if (!Flag[i][j] && G.Mat[i][j] < min.w) {
					min.w = G.Mat[i][j];
					min.a = i;
					min.b = j;
				}
		Flag[min.a][min.b] = 1; 
		count--;
		Q.push(min);
	}
	count = G.VecN - 1;
	edge now;
	while (count) {
		while (1) {
			now = Q.front();
			Q.pop();
			if (!((S.find(now.a) != S.end()) && (S.find(now.b) != S.end()))) {
				S.insert(now.a);
				S.insert(now.b);
				MCT.push_back(now);
				break;
			}
		}
		count--;
	}
	int i = 0;
	while (i < MCT.size()) {
		cout << "(" << MCT[i].a << "," << MCT[i].b << "):" << MCT[i].w << endl;
		i++;
	}
	return;
}
int main()
{
	cout << "=======TEST BEGIN=======" << endl;
	Graph G;
	Init_Graph(G);
	Prim(G, 0);
	Kruskal(G);
	cout << "=======TEST E N D=======" << endl;
	return 0;
}

