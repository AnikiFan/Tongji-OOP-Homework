#include<iostream>
using namespace std;
#define MAXN 500
struct Arc {
	int pos;
	Arc* next;
};
struct Vec {
	Arc* firstArc;
	int indegree;
};
typedef struct {
	Vec Vertices[MAXN];
	int ArcN;
	int VecN;
}Graph;//ÓÐÏòÍ¼
Graph row, col;
int row_sq[MAXN], col_sq[MAXN];
int main()
{
	for (int i = 1; i <= MAXN; i++) {
		row.Vertices[i].firstArc = NULL;
		row.Vertices[i].indegree = 0;
		col.Vertices[i].firstArc = NULL;
		col.Vertices[i].indegree = 0;
	}
	int k, n, m;
	cin >> k >> n >> m;
	row.VecN = k;
	col.VecN = k;
	row.ArcN = n;
	col.ArcN = m;
	int from, to;
	Arc* p = NULL;
	for (int i = 1; i <= n; i++) {
		cin >> from >> to;
		row.Vertices[to].indegree++;
		p = new Arc;
		if (!p) {
			cout << "OVERFLOW" << endl;
			return -2;
		}
		p->next = row.Vertices[from].firstArc;
		p->pos = to;
		row.Vertices[from].firstArc = p;
	}
	for (int i = 1; i <= m; i++) {
		cin >> from >> to;
		col.Vertices[to].indegree++;
		p = new Arc;
		if (!p) {
			cout << "OVERFLOW" << endl;
			return -2;
		}
		p->next = col.Vertices[from].firstArc;
		p->pos = to;
		col.Vertices[from].firstArc = p;
	}
	int rowtop = -1;
	while (1) {
		for (int i = 0; i < row.VecN; i++)
			if (!row.Vertices[i].indegree) {
				row.Vertices[i].indegree = rowtop;
				rowtop = i;
				p = row.Vertices[i].firstArc;
				while (p) {
					row.Vertices[p->pos].indegree--;
					p = p->next;
				}
				break;
			}
	}
	int top = 0;
	while (rowtop != -1) {
		row_sq[top++] = rowtop;
		rowtop = row.Vertices[rowtop].indegree;
	}
	if (top != row.VecN) {
		cout << -1;
		return 0;
	}
	int coltop = -1;
	while (1) {
		for (int i = 0; i < col.VecN; i++)
			if (!col.Vertices[i].indegree) {
				col.Vertices[i].indegree = coltop;
				coltop = i;
				p = col.Vertices[i].firstArc;
				while (p) {
					col.Vertices[p->pos].indegree--;
					p = p->next;
				}
				break;
			}
	}
	top = 0;
	while (coltop != -1) {
		col_sq[top++] = coltop;
		coltop = col.Vertices[coltop].indegree;
	}
	if (top != col.VecN) {
		cout << -1;
		return 0;
	}
	for (int i = 0; i < row.VecN; i++) {
		for (int j = 0; j < col.VecN; j++)
			if (col_sq[j] == row_sq[i])
				cout << col_sq[j] << " ";
			else
				cout << 0 << " ";
		cout << endl;
	}
	return 0;
}

