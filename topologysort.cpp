#include <iostream>
#include <stack>
#include <queue>

using namespace std;

void topologySort(vector<vector<int>>& edges){
	// 邻接链表法: 如果拓扑图是存在拓扑序列的, 则访问图中每个边一次, 每次取出一个点, 时间复杂度O(V + E)
	// 邻接链表存储, O(V + E), 邻接矩阵O(V^2)
	queue<int> que;
	vector<int> indegree(edges.size());
	// 初始化入度
	int count = 0;
	for(int i = 0; i < edges.size(); ++i){
		for(int j = 0; j < edges[i].size(); ++j){
			++indegree[edges[i][j]];
		}
	}
	// 将入度为零的点入队
	for(int i = 0; i < indegree.size(); ++i){
		if(indegree[i] == 0)
			que.push(i);
	}
	vector<int> output_order;
	while(!que.empty()){
		int tmp = que.front();
		que.pop();
		output_order.push_back(tmp);
		++count;
		for(int i = 0; i < edges[tmp].size(); ++i){
			int p = edges[tmp][i];
			--indegree[p];
			if(indegree[p] == 0){
				que.push(p);
			}
		}
	}
	if(count == edges.size()){
		for(int i = 0; i < output_order.size(); ++i){
			cout << output_order[i] << endl;
		}
	}
	else{
		cout << "No answers\n";
	}
}

void dfs(vector<vector<int>>& edges, vector<int>& visited, vector<int>& indegree, vector<int>& output_order, int nums){
	if(nums == edges.size()){
		for(int i = 0; i < output_order.size(); ++i){
			cout << output_order[i] << " ";
		}
		cout << endl;
		return ;
	}
	for(int i = 0; i < edges.size(); ++i){
		// 如果入度为0, 且未访问过, 则对其进行访问, 减少末点的入度
		if(!indegree[i] && !visited[i]){
			visited[i] = 1;
			for(int j = 0; j < edges[i].size(); ++j){
				int end_point = edges[i][j];
				indegree[end_point]--; // 减少入度
			}
			output_order[nums] = i;
			dfs(edges, visited, indegree, output_order, nums + 1); //
			// 回溯
			visited[i] = 0;
			for(int k = 0; k < edges[i].size(); ++k){
				int end_point = edges[i][k];
				indegree[end_point]++; // 增加出度
			}
		}
	}
	return ;
}

int main(){
	int n;
	cout << "Enter the number of vertex: ";
	cin >> n;
	vector<vector<int>> edges(n);
	while(true){
		cout << "enter the edge(i, j): ";
		int i, j;
		cin >> i >> j;
		if(i == -1 && j == -1){
			break;
		} 
		edges[i].push_back(j);
	}
	vector<int> indegree(edges.size());
	// 初始化入度
	int count = 0;
	for(int i = 0; i < edges.size(); ++i){
		for(int j = 0; j < edges[i].size(); ++j){
			++indegree[edges[i][j]];
		}
	}
	vector<int> visited(edges.size(), 0);
	vector<int> output_order(edges.size());
	dfs(edges, visited, indegree, output_order, 0);
	return 0;
} 