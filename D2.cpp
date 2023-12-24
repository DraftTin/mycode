#include <iostream>

using namespace std;

const int V_MAX = 15009;
const int E_MAX = 1009;
const int MAX = 99999999; 

class Node{
public:
	int d;
	int path_length;
	int pre;
	Node() : d(MAX), pre(-1), path_length(E_MAX) {}
};

class Edge{
public:
	int u, v;
	int weight;
};

bool smaller(Node V[], int n1, int n2){
	int path1[E_MAX];
	int path2[E_MAX];
	int k = n1;
	int path_length = V[n1].path_length;
	while(k != -1){
		path1[path_length--] = k;
		k = V[k].pre;
	}
	k = n2;
	path_length = V[n2].path_length;
	while(k != -1){
		path2[path_length--] = k;
		k = V[k].pre;
	}
	int len = V[n1].path_length + 1;
	int i = 0;
	while(path1[i] == path2[i]) {
		++i;
	}
	if(path1[i] > path2[i]) {
		// n1字典值大
		return false;
	}
	// n1字典值小
	return true;
}

void solution(Node V[], int len1, Edge E[], int len2){
	for(int i = 0; i < len1; ++i){
		int k = i;
		int pathLen = 0;
		while(k != 0 && k != -1){
			++pathLen;
			k = V[k].pre;
		}
		V[i].path_length = k != -1 ? pathLen : MAX; // 若没有到源节点的路径
	}
	for(int i = 0; i < len1; ++i){
		for(int j = 0; j < len2; ++j){
			if(V[E[j].v].pre == E[j].u || V[E[j].u].pre == -1) {
				// 若入点的pre已经是该边的出点或该边的出点是孤立点 则不需要进行比较 因为该点的路径不会输出
				continue;
			}
			int distance = V[E[j].u].d + E[j].weight;
			if(distance > V[E[j].v].d){
				// 距离更长不需要比较
				continue;
			}
			else if(distance == V[E[j].v].d){
				if(V[E[j].u].path_length + 1 > V[E[j].v].path_length){
					// 距离相同 经过节点数更多不需要比较
					continue;
				}
				else if(V[E[j].u].path_length + 1 < V[E[j].v].path_length){
					// 距离相同 经过节点数更少选择该点
					V[E[j].v].pre = E[j].u;
					V[E[j].v].path_length = V[E[j].u].path_length + 1;
				}
				else if(V[E[j].u].path_length + 1 == V[E[j].v].path_length){
					int flag = smaller(V, E[j].u, V[E[j].v].pre);
					// 距离相同 经过节点数相同 字典值更小选择该点 反之舍弃
					if(!flag) continue;
					V[E[j].v].pre = E[j].u;
				}
			}
		}
	}
}

void Bellmann_Ford(Node V[], int len1, Edge E[], int len2){
	V[0].d = 0;
	for(int i = 0; i < len1; ++i){
		for(int j = 0; j < len2; ++j){
			if(V[E[j].u].d + E[j].weight < V[E[j].v].d){
				V[E[j].v].d = V[E[j].u].d + E[j].weight;
				V[E[j].v].pre = E[j].u;
			}
		}
	}
	solution(V, len1, E, len2);
}



int main(void){
    int len1, len2;
    cin >> len1 >> len2;
    Node V[V_MAX];
    Edge E[E_MAX];
    for(int i = 0; i < len2; ++i){
        int x, y;
        int weight;
        cin >> x >> y >> weight;
        E[i].u = x;
        E[i].v = y;
        E[i].weight = weight;
    }
    Bellmann_Ford(V, len1, E, len2);
    int path[E_MAX];
    int path_length;
    for(int i = 1; i < len1; ++i){
    	if(V[i].pre == -1) continue;
    	// cout << "path_length = " << path_length << " i = " << i << endl;
    	int k = i; 
    	path_length = V[i].path_length;
    	while(k != -1){
    		path[path_length--] = k;
    		k = V[k].pre;
    	}
    	for(int j = 0; j < V[i].path_length; ++j){
    		cout << path[j] << "->";
    	}
    	cout << path[V[i].path_length];
    	if(i != len1 - 1){
    		cout << endl;
    	}
    }
    return 0;
}

/*
6 7
0 1 1
1 4 2
4 5 3
0 3 4
3 5 2
0 2 5
2 5 1
*/

/*
11 8
0 1 1
1 4 1
4 3 1
4 2 1
2 5 1
3 9 1
9 10 1
5 10 1
*/

/*
7 8
5 6 1
3 5 1
3 4 1
4 6 1
2 3 1
1 3 1
0 2 1
0 1 1
*/


