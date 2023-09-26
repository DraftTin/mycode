#include <iostream>
#include <vector>

#define MAX 99999

using namespace std;

class Node{
public:
	int d;
	int pre;
	Node() : d(MAX), pre(-1) {}
};

// void Dijkstra(vector<Node>& graph_list, int r){
// 	graph_list[r].d = 0;
// 	vector<int> visited(graph_list.size(), 0);
// 	for(int k = 0; k < graph_list.size(); ++k){
// 		int minval = MAX;
// 		int min;
// 		for(int i = 0; i < graph_list.size(); ++i){
// 			if(!visited[i] && graph_list[i].d < minval){
// 				minval = graph_list[i].d;
// 				min = i;
// 			}
// 		}
// 		visited[min] = 1;
// 		Edge * p = graph_list[min].first_edge;
// 		while(p != NULL){
// 			int distance = p->weight + graph_list[min].d;
// 			if(!visited[p->adjver] && distance < graph_list[p->adjver].d){
// 				graph_list[p->adjver].d = distance;
// 				graph_list[p->adjver].pre = min;
// 			}
// 			p = p->next;
// 		}
// 	}
// }


void Dijkstra(vector<Node>& V, vector<vector<int>>& E, int r){
	V[r].d = 0;
	vector<int> visited(V.size(), 0);
	for(int k = 0; k < V.size(); ++k){
		int minval = MAX;
		int min;
		for(int i = 0; i < V.size(); ++i){
			if(!visited[i] && V[i].d < minval){
				minval = V[i].d;
				min = i;
			}
		}
		visited[min] = 1;
		//cout << "selected point: " << min + 1 << "  dis: " << V[min].d << endl;
		// 每次取出一个结点
		// 取出距源节点最短的结点, 对和该节点为起点的边进行松弛操作
		// 循环V次, 循环内去除最小结点需要O(V), 对一个点的边进行放缩需要O(V), 总的时间复杂度O(V^2)
		// 如果用邻接链表表示图, 并且用二叉堆来取出最小元素, 总的时间复杂度可以下降到O(V * log(V) + E)
		//cout << "Before updating(edge from " << min + 1 << "): " << endl;
		// for(int i = 0; i < V.size(); ++i){
		// 	cout << V[i].d << " ";
		// }
		//cout << endl;
		for(int i = 0; i < V.size(); ++i){
			int distance = E[min][i] + V[min].d;
			if(!visited[i] && distance < V[i].d){
				V[i].d = distance;
				V[i].pre = min;
			}
		}
		// cout << "After updating(edge from " << min + 1 << "): " << endl;
		// for(int i = 0; i < V.size(); ++i){
		// 	cout << V[i].d << " ";
		// }
		// cout << endl;
	}
}
//邻接链表存储，每次Dijstra，循环V次, 查找最距离最小的点O(V), V次循环共访问边O(E), 总的O(E + V^2), 求出所有点的最短距离V次调用函数,最后时间复杂度O(V^3 + E * V) = O(V^3)
//
int main(void){
	cout << "enter the number of the vertex: ";
	int tmp;
	cin >> tmp;
	vector<Node> V(tmp);
	vector<Node> vv = V;
	vector<vector<int>> E(V.size(), vector<int>(V.size(), MAX));
	while(true){
		cout << "enter the edge and weight: ";
		int x, y, weight;
		cin >> x >> y >> weight;
		if(x == -1 && y == -1 && weight == -1)
			break;
		E[x][y] = weight;
	}
	vector<vector<Node>> res;
	for(int i = 0; i < V.size(); ++i){
		Dijkstra(V, E, i);
		res.push_back(V);
		V = vv;
	}
	int x, y, max = INT_MIN;
	for(int i = 0; i < res.size(); ++i){
		for(int j = 0; j < res.size(); ++j){
			cout << res[i][j].d << " ";
			if(res[i][j].d != MAX && max < res[i][j].d){
				x = i + 1;
				y = j + 1;
				max = res[i][j].d;
			}
		}
		cout << endl;
	}
	cout << "result: " << "x = " << x << "  y = " << y << "  diameter = " << max << endl;
	return 0;
}


/*
 5
 0 1 10
 1 2 1
 2 3 4
 3 2 6
 1 4 2
 4 1 3
 4 3 2
 3 0 7
 4 2 9
 0 4 5
 -1 -1 -1
*/

/*
6
0 1 50
0 3 10
1 2 10
1 3 15
2 4 30
3 0 20
3 4 15
4 1 20
4 2 35
5 4 3
-1 -1 -1
*/