#include <iostream>
#include <vector>

#define MAXD 99999

using namespace std;

// 求出每个点和其他点之间最短路径
// 动态规划：最优子结构 + 重叠子问题: i到j的最短距离取决于，i到其他点k，k再到j的最短距离
// 时间复杂度O(n^3)
// 理解：从节点i到节点j的一条不包括编号大于k的中间节点的路径
void Floyd_(vector<vector<int>>& graph_){
	for(int k = 0; k < graph_.size(); ++k){
		for(int i = 0; i < graph_.size(); ++i){
			for(int j = 0; j < graph_.size(); ++j){
				graph_[i][j] = min(graph_[i][j], graph_[i][k] + graph_[k][j]);
			}
		}
	}
}

void printGraph(vector<vector<int>>& graph_){
	for(int i = 0; i < graph_.size(); ++i){
		for(int j = 0; j < graph_.size(); ++j){
			cout << graph_[i][j] << " ";
		}
		cout << endl;
	}
}

int main(){
	cout << "enter the number of vertices:";
	int n;
	cin >> n;
	vector<vector<int>> graph_(n, vector<int>(n, MAXD));
	while(true){
		cout << "enter the edge(i->j) and weight: ";
		int i, j, weight;
		cin >> i >> j >> weight;
		if(i == -1 || j == -1){
			break;
		}
		graph_[i][j] = weight;
	}
	Floyd_(graph_);
	printGraph(graph_);
	return 0;
}