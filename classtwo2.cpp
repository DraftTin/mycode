#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Edge{
public:
	Edge * next;
	int adjver;
	Edge(int adj) : next(NULL), adjver(adj) {}
};

class Node{
public:
	Edge * first_edge;	//邻接链表
	Node() : first_edge(NULL) {}
};

void dfs(vector<Node>& graph_list, vector<int>& visited, int pos){
	// 输出深度优先树
	if(graph_list.size() - 1 < pos)
		return ;
	Edge * p = graph_list[pos].first_edge;
	cout << pos + 1 << " ";
	int flag = 1;
	while(p){
		int adj = p->adjver;
		if(!visited[adj]){
			visited[adj] = 1;
			dfs(graph_list, visited, adj);
		}
		p = p->next;
	}
}

void bfs(vector<Node>& graph_list, vector<int>& visited, int pos){
	// 输出广度优先树
	if(graph_list.size() - 1 < pos){
		return ;
	}
	queue<int> que;
	que.push(pos);
	while(!que.empty()){
		int tmp = que.front(); 	
		que.pop();
		cout << tmp + 1 << " ";
		Edge * edge = graph_list[tmp].first_edge;
		while(edge){
			if(!visited[edge->adjver]){
				visited[edge->adjver] = 1;
				que.push(edge->adjver);
			}
			edge = edge->next;
		}
	}
}

int main(){
	cout << "enter the number of the vertice: ";
	int n;
	cin >> n;
	vector<Node> graph_list(n);
	while(true){
		cout << "enter the edge(i->j) or enter -1, -1 to exit: ";
		int i, j;
		cin >> i >> j;
		if(i == -1 && j == -1){
			break;
		}
		i = i - 1;
		j = j - 1;
		Edge * edge = new Edge(j);
		if(graph_list[i].first_edge == NULL){
			graph_list[i].first_edge = edge;
		}
		else{
			if(graph_list[i].first_edge->adjver > j){
				edge->next = graph_list[i].first_edge;
				graph_list[i].first_edge = edge;
			}
			else{
				Edge * p = graph_list[i].first_edge;
				while(p->next && p->next->adjver < j){
					p = p->next;
				}
				edge->next = p->next;
				p->next = edge;
			}
		}
	}
	// Edge * p = graph_list[0].first_edge;
	// while(p){
	// 	cout << p->adjver + 1 << endl;
	// 	p = p->next;
	// }
	// cout << endl;
	vector<int> visited1(graph_list.size(), 0);
	vector<int> visited2(graph_list.size(), 0);
	visited1[0] = 1;
	visited2[0] = 1;
	// cout << "bfs: " << endl;
	// bfs(graph_list, visited1, 0);
	// cout << endl;
	cout << "dfs: " << endl;
	dfs(graph_list, visited2, 0);
	return 0;
}

/*
5
1 2
1 3
3 4
2 5
-1 -1 
*/

/*
6
1 5
2 3
3 6
2 4
6 4
1 2
5 6
-1 -1
*/