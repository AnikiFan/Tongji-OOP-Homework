#include<iostream>
#define ERROR 0
#define OK 1
using namespace std;
typedef int Status;
typedef struct Arc {
	Arc* next;
	int Adjvex;
}Arc;
typedef struct {
	Arc* firstArc;
	int AdjVex;
	int w;
	int indegree;
	int e;
	int l;
} Vex;
typedef struct {
	Vex* Vertices;
	int vexnum;
	int arcnum;
	int* topo;
}Graph;
Status InitGraph(Graph& G)
{
	cin >> G.vexnum;
	G.Vertices = new Vex[G.vexnum];
	if (!G.Vertices) {
		cout << "OVERFLOW" << endl;
		getchar();
		return -2;
	}
	for (int i = 0; i < G.vexnum; i++)
		G.Vertices[i].firstArc = NULL;
	int from;
	Arc* p = NULL;
	for (int i = 0; i < G.vexnum; i++) {
		cin >> G.Vertices[i].w;
		cin >> G.Vertices[i].indegree;
		for (int j = 0; j < G.Vertices[i].indegree; j++) {
			cin >> from;
			from--;
			p = new Arc;
			if (!p) {
				cout << "OVERFLOW" << endl;
				getchar();
				return -2;
			}
			p->Adjvex = i;
			p->next = G.Vertices[from].firstArc;
			G.Vertices[from].firstArc = p;
		}
	}
	G.topo = new int[G.vexnum];
	if (!G.topo) {
		cout << "OVERFLOW" << endl;
		getchar();
		return -2;
	}
	return OK;
}
Status TopoOrder(Graph& G)
{
	int top = -1;
	for (int i = 0; i < G.vexnum; i++)
		if (!G.Vertices[i].indegree) {
			G.Vertices[i].indegree = top;
			top = i;
		}
	int count = 0;
	Arc* p = NULL;
	while (top + 1) {
		G.topo[count++] = top;
		p = G.Vertices[top].firstArc;
		top = G.Vertices[top].indegree;
		while (p) {
			G.Vertices[p->Adjvex].indegree--;
			if (!G.Vertices[p->Adjvex].indegree) {
				G.Vertices[p->Adjvex].indegree = top;
				top = p->Adjvex;
			}
			p = p->next;
		}
	}
	if (count != G.vexnum) {
		cout << "count:" << count << endl;
		cout << "ERROR" << endl;
		getchar();
		return ERROR;
	}

	return OK;
}
Status GetVe(Graph& G)
{
	for (int i = 0; i < G.vexnum; i++)
		G.Vertices[i].e = 0;
	Arc* p;
	for (int i = 0; i < G.vexnum; i++) {
		p = G.Vertices[G.topo[i]].firstArc;
		while (p) {
			if (G.Vertices[p->Adjvex].e < G.Vertices[G.topo[i]].e + G.Vertices[G.topo[i]].w)
				G.Vertices[p->Adjvex].e = G.Vertices[G.topo[i]].e + G.Vertices[G.topo[i]].w;
			p = p->next;
		}
	}
	return OK;
}
Status GetVl(Graph& G)
{
	int max = 0;
	int maxn;
	for (int i = 0; i < G.vexnum; i++)
		if (G.Vertices[i].w + G.Vertices[i].e > max) {
			max = G.Vertices[i].w + G.Vertices[i].e;
			maxn = i;
		}
	for (int i = 0; i < G.vexnum; i++)
		if (!G.Vertices[i].firstArc)
			G.Vertices[i].l = max - G.Vertices[i].w;
		else
			G.Vertices[i].l = max;
	Arc* p = NULL;
	for (int i = G.vexnum - 2; i >= 0; i--) {
		p = G.Vertices[G.topo[i]].firstArc;
		while (p) {
			if (G.Vertices[G.topo[i]].l > G.Vertices[p->Adjvex].l - G.Vertices[G.topo[i]].w)
				G.Vertices[G.topo[i]].l = G.Vertices[p->Adjvex].l - G.Vertices[G.topo[i]].w;
			p = p->next;
		}
	}
	return OK;
}
int main()
{
	Graph G;
	InitGraph(G);
	TopoOrder(G);
	GetVe(G);
	GetVl(G);
for (int i = 0; i < G.vexnum; i++)
		cout << G.Vertices[i].e + G.Vertices[i].w << " " << (G.Vertices[i].e == G.Vertices[i].l ? 1 : 0) << endl;
	return 0;
}

