#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 99999

using namespace std;

class Node{
public:
	int d;
	int father;
	int rank;
	Node() : rank(0), d(MAX), father(-1) {}
};

class Edge{
public:
	int i;
	int j; 		// 边的两个端点
	int weight;
	Edge(int ii, int jj, int w) : i(ii), j(jj), weight(w) {}
};

inline bool cmp(Edge& a, Edge& b) {return a.weight < b.weight;}

// 并查集的操作: Father 返回结点的祖先结点并压缩路径，Union 将两个集合按秩合并

int Father(vector<Node>& V, int i){
	// 返回树的根节点，附带压缩路径
	if(V[i].father != i){
		V[i].father = Father(V, V[i].father);
	}
	return V[i].father;
}

void Link(vector<Node>& V, int i, int j){
	// 将结点j合并到i所在的树中，被Union调用
	V[j].father = Father(V, i);
}

void Union(vector<Node>& V, int i, int j){
	if(V[i].rank > V[j].rank){
		Link(V, i, j);
	}
	else{
		Link(V, j, i);
		if(V[i].rank == V[j].rank) ++V[j].rank;
	}
}

vector<Edge> MinimumSpanningTree(vector<Node>& V, vector<Edge>& E){
	// 基于并查集的 Kruskal's Algorithm
	// 时间复杂度, 对边进行排序O(Elog(E)), 选取边O(E), 所以总体上 O(Elog(E)), 若非稠密图, 时间复杂度O(Vlog(V)), 适合非稠密图
	vector<Edge> A;
	for(int i = 0; i < V.size(); ++i)
		V[i].father = i;
	sort(E.begin(), E.end(), cmp);
	for(const Edge& edge : E){
		if(Father(V, edge.i) != Father(V, edge.j)){
			//cout << "Selected edge: " << edge.i + 1 << "--" << edge.j + 1 << endl;
			Union(V, edge.i, edge.j);
			A.push_back(edge);
		}
	}
	return A;
}

vector<Edge> MaximumSpanningTree(vector<Node>& V, vector<Edge>& E){
	// 求最大生成树，将权值置负求最小生成树即为所求
	vector<Edge> EE = E;
	for(Edge& tmp : EE) tmp.weight = -tmp.weight;
	vector<Edge> A = MinimumSpanningTree(V, EE);
	for(Edge& tmp : A) tmp.weight = -tmp.weight;
	return A;
}

int main(void){
	int count;
	cout << "enter the number of vertex:";
	cin >> count;
	vector<Node> V(count);
	vector<Edge> E;
	while(true){
		cout << "enter the i, j and weight: ";
		int i, j, weight;
		cin >> i >> j >> weight;
		if(i == -1 && j == -1)
			break;
		E.push_back(Edge(i, j, weight));
	}
	vector<Edge> A = MaximumSpanningTree(V, E);
	int cost = 0;
	for(const Edge& tmp : A){
		cout << tmp.i + 1 << " " << tmp.j + 1 << " " << tmp.weight << endl;
		cost += tmp.weight;
	}
	cout << "The min cost :" << cost << endl;
	return 0;
}

/*
9
0 1 4
0 7 8
1 7 11
1 2 8
2 3 7
2 5 4
2 8 2
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7
-1 -1 -1
*/

/*
6
0 1 16
0 4 19
0 5 21
1 5 11 
1 2 5
1 3 6
2 3 10
3 4 18
3 5 14
4 5 33
-1 -1 -1
*/