#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <stack>

using namespace std;

int count = 0;

void dfsWithoutRecursion(vector<int>& vertices, vector<vector<int>>& edges){
	vector<int> visited(vertices.size(), 0);
	stack<int> sta;
	sta.push(0);
	cout << 0 << endl;
	visited[0] = 1;
	while(!sta.empty()){
		int tmp = sta.top();
		int flag = 0;
		//对与该点相邻的点进行遍历, 如果未访问过, 则入栈并对该点进行访问
		for(int i =  0; i < vertices.size(); ++i){
			if(edges[tmp][i] == 1 && visited[i] == 0){
				sta.push(i);
				cout << i << endl;
				visited[i] = 1;
				flag = 1;
				break;
			}
			++count;
		}
		if(!flag)
			sta.pop();
	}
}

void dfsWithoutRecursion2(vector<int>& vertices, vector<vector<int>>& edges){
	// 时间复杂度O(V^2), 如果使用邻接链表实现可改善为O(V + E)
	vector<int> visited(vertices.size(), 0);
	stack<int> sta;
	sta.push(0);
	visited[0] = 1;
	while(!sta.empty()){
		int tmp = sta.top();
		sta.pop();
		cout << tmp << endl;
		for(int i = 0; i < vertices.size(); ++i){
			if(!visited[i] && edges[tmp][i] == 1){
				sta.push(i);
				visited[i] = 1;
			}
		}
	}
}

int main(){
	vector<int> vertices(5);
	vector<vector<int>> edges(vertices.size(), vector<int>(vertices.size(), 0));
	while(true){
		int x, y;
		cout << "enter the two adjacent points(x to y): ";
		cin >> x >> y;
		if(x == -1 && y == -1)
			break;
		edges[x][y] = 1;
	}
	dfsWithoutRecursion2(vertices, edges);
	cout << "count = " << count << endl;
	return 0;
}