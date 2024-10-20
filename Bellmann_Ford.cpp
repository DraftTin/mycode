#include <iostream>
#include <vector>

using namespace std;

// 结点字段d标记节点到起始结点当前的最短距离，pre表示前继结点号
class Node{
public:
	int d;
	int pre;
	Node() : d(INT_MAX), pre(-1) {}
};

// 边字段u表示起始结点号，v表示边的中止节点号，weight表示边的长度
class edge{
public:
	int u, v;
	int weight;
	edge(int i, int j, int w) : u(i), v(j), weight(w) {}
};

// 根据松弛定理可知，<v0, v1, v2..vk>, 是从源节点s到目标结点vk的最短路径，如果松弛的顺序是<v0, v1> <v1, v2>,..,<v_(k-1), vk>，则vk.d == delta(s, vk), delta表示最短距离
// 该操作和任何其他的松弛操作无关
// 遍历图中的边V次, 时间复杂度O(VE)
// bellmann ford algorithm doesn't support negative loop but can detect negative loop
bool Bellmann_Ford(vector<Node> &V, vector<edge> &E, int k){
	V[k].d = 0;
	for(int i = 0; i < V.size() - 1; ++i){
		for(int j = 0; j < E.size(); ++j){
			if(V[E[j].u].d + E[j].weight < V[E[j].v].d){
				V[E[j].v].d = V[E[j].u].d + E[j].weight;
				V[E[j].v].pre = E[j].u;
			}
		}
	}
	for(int i = 0; i < E.size(); ++i){
		if(V[E[i].v].d > V[E[i].u].d + E[i].weight){
			cout << "error " << endl;
			return false;
		}
	}
	return true;
}

int main(void){
    cout << "enter the number of vertex:";
    int tmp;
    cin >> tmp;
    vector<Node> V(tmp);
    vector<edge> E;
    while(true){
        cout << "Please enter two adjacent points and weight: ";
        int x, y;
        int weight;
        cin >> x >> y >> weight;
        if(x == -1 && y == -1 && weight == -1)
            break;
        edge *tmp = new edge(x, y, weight);
        E.push_back(*tmp);
        delete tmp;
    }
    if(Bellmann_Ford(V, E, 0)){
	 	for(int i = 0; i < V.size(); ++i){
	 		cout << i << " to 0 : ";
	 		int k = i;
		 	while(k != -1){
		 		cout << k << " ";
		 	 	k = V[k].pre;
		 	}
		 	cout << endl;
		 }
 	}
    return 0;
}
/*
5
0 1 6
0 2 7
1 3 -4
2 4 -3
1 4 5
4 1 -2
2 3 9
3 4 7
3 0 2
-1 -1 -1
*/
