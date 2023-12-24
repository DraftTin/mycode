#include <iostream>
#include <vector>
#include <cmath>

#define int_max 9999

using namespace std;

void Extend_shortest_Pathes(vector<vector<int>>& L, vector<vector<int>>& W){
	// 等价于矩阵乘法
	for(int i = 0; i < L.size(); ++i){
		for(int j = 0; j < L.size(); ++j){
			int l = int_max;
			for(int k = 0; k < L.size(); ++k){
				l = min(l, L[i][k] + W[k][j]);
			}
			L[i][j] = l;
		}
	}
}

vector<vector<int>> Slow_All_Pairs_Shortest_Pathes(vector<vector<int>>& W){
	vector<vector<int>> L(W.size(), vector<int>(W.size(), int_max));
	for(int i = 0; i < L.size(); ++i)
		L[i][i] = 0;
	for(int i = 0; i < W.size() - 1; ++i){
		Extend_shortest_Pathes(L, W);
	}
	return L;
}

vector<vector<int>> Faster_All_Pairs_Shortest_Pathes(vector<vector<int>>& W){
	// L(n+1) = L(n) * W
	// L(2m) = L(m) * L(m)
	// 由于L(n-1) = L(m), 当m >= n-1时
	// 可以让循环进行log(W.size())取顶次
	vector<vector<int>> L = W;
	int n = ceil(sqrt(W.size()));
	for(int i = 0; i < n; ++i){
		Extend_shortest_Pathes(L, L);
	}
	return L;
}

vector<vector<int>> allShortestPaths(vector<vector<int>>& graph_list){
	// 动态规划方法求解 对于Ak(i, j)表示中间节点下标小于或等于k时，<i, j>的最短距离
	// 由于矩阵下标从0开始，所以映射到具体A矩阵时k需要加1
	// 时间复杂度O(n^3)，很规整所以比调用n次Dijstra的常数项会小很多，条件也只是不允许出现负环
	for(int k = 0; k < graph_list.size(); ++k){
		for(int i = 0; i < graph_list.size(); ++i){
			for(int j = 0; j < graph_list.size(); ++j){
				graph_list[i][j] = min(graph_list[i][k] + graph_list[k][j], graph_list[i][j]);
			}
		}
	}
}

int main(void){
	cout << "enter the number of vertices:";
	int count;
	cin >> count;
	vector<vector<int>> E(count, vector<int>(count, int_max));
	for(int i = 0; i < E.size(); ++i)
		E[i][i] = 0;
	while(true){
		cout << "enter i, j and weight: ";
		int i, j, weight;
		cin >> i >> j >> weight;
		if(i == -1 && j == -1)
			break;
		E[i][j] = weight;
	}
	//cout << E[1][3] << " " << E[3][0] << endl;
	vector<vector<int>> L = Faster_All_Pairs_Shortest_Pathes(E);
	for(int i = 0; i < L.size(); ++i){
		for(int j = 0; j < L.size(); ++j){
			if(L[i][j] > 9000)
				cout << '#' << "  ";
			else
				cout << L[i][j] << "  ";
		}
		cout << endl;
	}
	return 0;
}

/*
0 1 3
0 2 8
0 4 -4
1 3 1
1 4 7
2 1 4
3 2 -5
3 0 2
4 3 6
-1 -1 -1
*/