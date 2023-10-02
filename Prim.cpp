#include <iostream>
#include <vector>

using namespace std;

class Edge{
public:
	Edge * next;
	int weight;
	int adjver;
	Edge() : next(NULL), adjver(-1), weight(-1) {}
};

class Node{
public:
	int key;	// 距prim树的最短距离
	int father; // 父节点
	Edge * first_edge;
	Node() : key(INT_MAX), father(-1), first_edge(NULL) {}
};

// 算法: 和Dijstra相似, 取出最近的点之后, 对这个点上的边上的另一端的点的距离进行调整
// 如果使用最小优先队列实现，每次取出距离最小的点，之后调整最小堆V次，共V * log(V), 取出后调整其他节点的距离, 所有循环共访问2E次边, 
// 每次调整后附带节点在最小堆中上浮的操作log(V)，所以共E * log(V)
// 最后的时间复杂度O(Vlog(V) + Elog(V))
void Prim(vector<Node>& graph_list){
	// 每次循环取出一个距离prim树最近的点, O(V), 共进行V次, 每条边访问两次O(2E), 总的时间复杂度: O(V^2 + E) = O(V^2), 适合稠密图
	vector<bool> visited(graph_list.size(), false);
	graph_list[0].key = 0;
	for(int i = 0; i < graph_list.size(); ++i){
		int min = INT_MAX;
		int mindex;
		for(int j = 0; j < graph_list.size(); ++j){
			if(!visited[j] && graph_list[j].key < min){
				mindex = j;
				min = graph_list[j].key;
			}
		}
		visited[mindex] = true;
		// cout << "Selected point: " << mindex + 1 << "  dis: " << graph_list[mindex].key << endl;
		Edge * p = graph_list[mindex].first_edge;
		while(p != NULL){ 
			if(!visited[p->adjver]){
				// cout << "dis[" << p->adjver + 1 << "] = " << graph_list[p->adjver].key << endl;
				// cout << "edge(" << mindex + 1 << "--" << p->adjver + 1 << ") weight = " << p->weight << endl;
				if(graph_list[p->adjver].key > p->weight){
					//cout << "dis[edge->adjver]  <- " << p->weight << endl;
					graph_list[p->adjver].father = mindex;
					graph_list[p->adjver].key = p->weight;
				}
				//else
					//cout << "pass" << endl;
			}
			p = p->next;
		}
	}
	int cost = 0;
	for(int i = 1; i < graph_list.size(); ++i){
		cout << i + 1 << "--" << graph_list[i].father + 1 << "  weight: " << graph_list[i].key << endl;
		cost += graph_list[i].key;
	}
	cout << endl;
	cout << "cost = " << cost << endl;
}

int main(){
	int n;
	cout << "enter the number of vertices: ";
	cin >> n;
	vector<Node> graph_list(n);
	while(true){
		cout << "enter the edge(x--y) and weight: ";
		int x, y, weight;
		cin >> x >> y >> weight;
		if(x == -1 && y == -1)
			break;
		Edge * edge1 = new Edge();
		edge1->weight = weight;
		edge1->adjver = y;
		if(graph_list[x].first_edge == NULL){
			graph_list[x].first_edge = edge1;
		}
		else{
			edge1->next = graph_list[x].first_edge->next;
			graph_list[x].first_edge->next = edge1;
		}
		Edge * edge2 = new Edge();
		edge2->weight = weight;
		edge2->adjver = x;
		if(graph_list[y].first_edge == NULL){
			graph_list[y].first_edge = edge2;
		}
		else{
			edge2->next = graph_list[y].first_edge->next;
			graph_list[y].first_edge->next = edge2;
		}
	}
	Prim(graph_list);
	return 0;
}

/*
9
0 1 4
1 2 8
2 3 7
3 4 9
4 5 10
5 6 2
6 7 1
7 8 7
7 0 8
7 1 11
6 8 6
8 2 2
2 5 4
3 5 14
-1 -1 5
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

/*
7
0 1 8
0 3 5
1 3 3
1 2 12
1 4 10
2 4 6
2 5 2
4 5 9
3 5 7
3 6 15
-1 -1 -1
*/