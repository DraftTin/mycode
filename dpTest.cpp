#include <iostream>
#include <vector>

using namespace std;

class Edge{
public:
	Edge * next;
	int adjver;
	int weight;
	Edge() : next(NULL) {}
};

class Node{
public:
	Edge * first_edge;
	int indegree;
	Node() : first_edge(NULL), indegree(0) {}
};

// 输入图中的节点和有向线段 返回源节点到终节点的最小距离和路径
vector<int> solution(vector<Node>& graph_list, int k, int& total_cost){
	// path.size() 即为层数
	// graph_list[0]为源节点  graph_list[size - 1]为终点
	// 算法：从后向前求出节点到终点的最短距离，每一个节点都到终点的路径都是最优的
	// 时间复杂度：每条边遍历一次，每个点遍历一次 O(V + E) = O(V)
	vector<Edge*> next(graph_list.size()); // 表示图中各个点到终点最短路径中的下一个点
	vector<int> cost(graph_list.size(), 0);  // 表示图中各个点到终点的最短距离，均初始化为0
	for(int i = graph_list.size() - 1; i >= 0; --i){
		// 求min{edge_ij + cost[j]}做为cost[i]
		Edge * edge = graph_list[i].first_edge;
		int minDis = INT_MAX;
		while(edge){
			int j = edge->adjver;
			int dis = cost[j] + edge->weight;
			if(dis < minDis){
				minDis = dis;
				next[i] = edge;
				cost[i] = edge->weight + cost[j];
			}
			edge = edge->next;
		}
	}
	vector<int> path(k);
	total_cost = 0;
	path[0] = 0;
	for(int i = 1; i < path.size(); ++i){
		cout << next[path[i - 1]]->weight << endl;
		total_cost += next[path[i - 1]]->weight;
		path[i] = next[path[i - 1]]->adjver;
	}
	// cout << cost[0] << endl;
	return path;
}

/*
3
3
0 1 1
1 2 1
-1 -1 -1
*/

int main(){
	int num;
	cout << "enter the number of vertice: ";
	cin >> num;
	int k;
	cout << "enter the number of layers: ";
	cin >> k;
	vector<Node> graph_list(num);
	while(true){
		cout << "enter the i->j and weight: ";
		int i, j, weight;
		cin >> i >> j >> weight;
		if(i == -1 && j == -1){
			break;
		}
		Edge * edge = new Edge();
		edge->adjver = j;
		edge->weight = weight;
		if(graph_list[i].first_edge == NULL){
			graph_list[i].first_edge = edge;
		}
		else{
			edge->next = graph_list[i].first_edge->next;
			graph_list[i].first_edge->next = edge;
		}
		++graph_list[j].indegree;
	}
	int total_cost;
	vector<int> path = solution(graph_list, k, total_cost);
	for(int tmp : path){
		cout << tmp << "->";
	}
	cout << "NULL" << endl;
	cout << "dis = " << total_cost << endl;
	return 0;
}

/*
12
5
0 1 9
0 2 7
0 3 3
0 4 2
1 5 4
1 6 2
1 7 1
2 5 2
2 6 7
3 7 11
4 6 11
4 7 8
5 8 6
5 9 5
6 8 4
6 9 3
7 9 5
7 10 6
8 11 4
9 11 2
10 11 5
-1 -1 -1
*/

