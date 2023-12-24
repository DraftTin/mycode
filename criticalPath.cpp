#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class Edge{
public:
	int ete;		// 活动<vi, vj>的最早发生时间 = vi.etv
	int lte;		// 活动<vi, vj>的最晚发生时间 = vi.ltv - weight(<vi, vj>)
	int weight;		// 活动代价
	int adjver;		// 边的入点
	Edge * next;	// 邻接链表next指针
	Edge() : next(NULL) {}
};

class Node{
public:
	int etv;			// 事件的最早发生时间
	int ltv;			// 事件的最晚发生时间
	int indegree;		// 入度
	Edge * first_edge;	// 邻接链表的头指针
	Node() : first_edge(NULL), indegree(0) {}
};


void dfs(vector<Node>& graph_list, vector<bool>& visited, int pos, vector<int>& path, int nums){
	if(nums > 0 && path[nums - 1] == graph_list.size() - 1){
		for(int i = 0; i < nums; ++i){
			cout << path[i] << " ";
		}
		cout << endl;
		return ;
	}
	Edge * edge = graph_list[pos].first_edge;
	while(edge){
		int t = edge->adjver;
		if(!visited[t] && edge->ete == edge->lte){
			visited[t] = true;
			path[nums] = t;
			dfs(graph_list, visited, t, path, nums + 1);
			visited[t] = false;
		}
		edge = edge->next;
	}
}

stack<int> topologicalSort(vector<Node>& graph_list){
	for(int i = 0; i < graph_list.size(); ++i)
		graph_list[i].etv = 0;
	queue<int> que;
	stack<int> sta;
	int cnt = 0;
	// 将入度为零的点入队，即源节点入队
	for(int i = 0; i < graph_list.size(); ++i){
		if(graph_list[i].indegree == 0) que.push(i);
	}
	// 初始化每个结点的etv即最早发生时间为0，之后要开始增大
	for(int i = 0; i < graph_list.size(); ++i){
		graph_list[i].etv = 0;
	}
	while(!que.empty()){
		int tmp = que.front();
		que.pop();
		sta.push(tmp); // 将队列中弹出的结点压入栈中，栈中从底到顶是拓扑序
		++cnt;
		Edge * edge = graph_list[tmp].first_edge;
		// 删除结点的同时更新边链表中末点的入度
		while(edge){
			int p = edge->adjver;
			if(!--graph_list[p].indegree) que.push(p);
			graph_list[p].etv = max(graph_list[p].etv, edge->weight + graph_list[tmp].etv);
			edge->ete = graph_list[tmp].etv;
			edge = edge->next;
		}
	}
	// cout << "cnt = " << cnt << endl;
	if(cnt != graph_list.size()) sta.push(-1);
	return sta;
} 

void criticalPath(vector<Node>& graph_list){
	stack<int> sta = topologicalSort(graph_list);
	int tmp = sta.top();
	if(tmp == -1){
		cout << "circle" << endl;
		return ;
	}
	
	// 将每个点的最晚发生时间初始化为汇点的etv
	for(int i = 0; i < graph_list.size(); ++i){
		graph_list[i].ltv = graph_list[tmp].etv;
	}
	while(!sta.empty()){
		tmp = sta.top();
		sta.pop();
		Edge * edge = graph_list[tmp].first_edge;
		while(edge){
			graph_list[tmp].ltv = min(graph_list[tmp].ltv, graph_list[edge->adjver].ltv - edge->weight);
			edge->lte = graph_list[edge->adjver].ltv - edge->weight;
			edge = edge->next;
		}
	}
}

int main(){
	int num;
	cout << "enter the number of vertice: ";
	cin >> num;
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
	vector<int> path(graph_list.size());
	vector<bool> visited(graph_list.size(), false);
	criticalPath(graph_list);
	visited[0] = true;
	path[0] = 0;
	dfs(graph_list, visited, 0, path, 1);
	return 0;
}

/*
4
0 1 1
0 2 1
1 3 1
2 3 1
-1 -1 -1
*/

/*
10
0 1 3
0 2 4
1 3 5
2 3 8
1 4 6
3 4 3
2 5 7
5 7 6
4 7 4
4 6 9
6 9 2
7 8 5
8 9 3
-1 -1 -1
*/




// 边的存储, 用链表实现的版本
/*class Edge{
public:
	int weight;
	int adjver;
	Edge * next;
	Edge() : next(NULL) {}
};

class Node{
public:
	int etv;
	int ltv;
	int indegree;
	Edge * first_edge;
	Node() : first_edge(NULL), indegree(0) {}
};

stack<int> topologicalSort(vector<Node>& graph_list){
	for(int i = 0; i < graph_list.size(); ++i)
		graph_list[i].etv = 0;
	stack<int> sta;
	stack<int> res;
	for(int i = 0; i < graph_list.size(); ++i){
		if(graph_list[i].indegree == 0)
			sta.push(i);
	}
	int count = 0;
	while(!sta.empty()){
		int tmp = sta.top();
		res.push(tmp);
		sta.pop();
		++count;
		Edge * p = graph_list[tmp].first_edge;
		while(p != NULL){
			if(--graph_list[p->adjver].indegree == 0){
				sta.push(p->adjver);
			}
			if(p->weight + graph_list[tmp].etv > graph_list[p->adjver].etv){
				graph_list[p->adjver].etv = p->weight + graph_list[tmp].etv;
			}
			p = p->next;
		}
	}
	if(count != graph_list.size())
		res.push(-1);
	return res;
} 

void criticalPath(vector<Node>& graph_list){
	stack<int> sta = topologicalSort(graph_list);
	if(sta.top() == -1){
		cout << "error" << endl;
		return ;
	}
	for(int i = 0; i < graph_list.size(); ++i){
		graph_list[i].ltv = graph_list[graph_list.size() - 1].etv;
	}
	while(!sta.empty()){
		int tmp = sta.top();
		sta.pop();
		Edge * edge = graph_list[tmp].first_edge;
		while(edge != NULL){
			if(graph_list[tmp].ltv > graph_list[edge->adjver].ltv - edge->weight){
				graph_list[tmp].ltv = graph_list[edge->adjver].ltv - edge->weight;
			}
			edge = edge->next;
		}
	}
	for(int i = 0; i < graph_list.size(); ++i){
		cout << i << ": " << "etv = " << graph_list[i].etv << "   ltv = " << graph_list[i].ltv << endl;
	}
	for(int i = 0; i < graph_list.size(); ++i){
		if(graph_list[i].etv == graph_list[i].ltv){
			cout << i << " ";
		}
	}
}

int main(){
	int num;
	cout << "enter the number of vertice: ";
	cin >> num;
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
	criticalPath(graph_list);
	return 0;
}*/