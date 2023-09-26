#include <iostream>

using namespace std;

const int MAX = 20009; 

class Node{
public:
	int d;
	int ss_number; // subway station number  表示起点到该点中最小的地铁编号，若没有则赋值MAX
	int pre;
	Node() : d(MAX), pre(-1), ss_number(MAX) {}
};

class Edge{
public:
	int u, v;
	int weight;
};

void Bellmann_Ford(Node V[], int n, Edge E[], int m, int k, int s, int t){
	// 车站编号从1开始 (s - 1)表示小明的起点站  (t - 1)表示小明的终点站
	V[s - 1].d = 0;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < (m + k) * 2; ++j){
			if(V[E[j].u].d + E[j].weight < V[E[j].v].d){
				V[E[j].v].d = V[E[j].u].d + E[j].weight;
				V[E[j].v].pre = E[j].u;
				V[E[j].v].ss_number = V[E[j].u].ss_number; // 由于线路改变 最小地铁乘坐编号也修改
				if(j >= 2 * m && V[E[j].v].ss_number > E[j].u){
					// cout << "##: " << j << " " << E[j].u << " " << E[j].v << " " << E[j].weight << endl;
					// 若出发的地点是地铁站 从2*m开始是地铁的线路 且出发的地铁站编号比当前已经标记的小 则更新
					V[E[j].v].ss_number = E[j].u;
				}
			}
			else if(V[E[j].u].d + E[j].weight == V[E[j].v].d && V[E[j].u].ss_number < V[E[j].v].ss_number){
				// 若地铁编号更小则修改
				V[E[j].v].pre = E[j].u;
				V[E[j].v].ss_number = V[E[j].u].ss_number; 
				if(j >= 2 * m && V[E[j].v].ss_number > E[j].u){
					V[E[j].v].ss_number = E[j].u;
				}
			}
		}
	}
}

int main(void){
	int n, s, t;
	cin >> n >> s >> t;
	int m;
	cin >> m;
    Node V[MAX];
    Edge E[MAX];
    for(int i = 0; i < m; ++i){
        int x, y;
        int weight;
        cin >> x >> y >> weight;
        E[2 * i].u = x - 1;
        E[2 * i].v = y - 1;
        E[2 * i].weight = weight;
        E[2 * i + 1].u = y - 1;
        E[2 * i + 1].v = x - 1;
        E[2 * i + 1].weight = weight; 
    }
    int k;
    cin >> k;
    for(int i = 0; i < k; ++i){
        int x, y;
        int weight;
        cin >> x >> y >> weight;
        E[2 * m + 2 * i].u = x - 1;
        E[2 * m + 2 * i].v = y - 1;
        E[2 * m + 2 * i].weight = weight;
        E[2 * m + 2 * i + 1].u = y - 1;
        E[2 * m + 2 * i + 1].v = x - 1;
        E[2 * m + 2 * i + 1].weight = weight; 
    }

    Bellmann_Ford(V, n, E, m, k, s, t);

    cout << V[t - 1].d << endl;
    if(V[t - 1].ss_number == MAX){
    	cout << "only bus";
    }
    else{
    	cout << V[t - 1].ss_number + 1;
    }
    return 0;
}


// int main(){
// 	Node sites(MAX);
// 	int n, s, t;
// 	cin >> n >> s >> t;
// 	int m;
// 	cin >> m;
// 	for(int i = 0; i < m; ++i){
// 		int a, b, c;
// 		cin >> a >> b >> c;
// 		// 创建a->b
// 		Edge * edge1 = new Edge();
// 		edge1.weight = c;
// 		edge1.adjver = b;
// 		edge1->next = sites[a].first_edge;
// 		sites[a].first_edge = edge1;
// 		// 创建b->a
// 		Edge * edge2 = new Edge();
// 		edge2.weight = c;
// 		edge2.adjver = a;
// 		edge2->next = sites[b].first_edge;
// 		sites[a].first_edge = edge2;
// 	}
// 	int k;
// 	cin >> k;
// 	for(int i = 0; i < k; ++i){
// 		int a, b, c;
// 		cin >> a >> b >> c;
// 		// 创建a->b
// 		Edge * edge1 = new Edge();
// 		edge1.weight = c;
// 		edge1.adjver = b;
// 		edge1->next = sites[a].first_edge;
// 		sites[a].first_edge = edge1;
// 		// 创建b->a
// 		Edge * edge2 = new Edge();
// 		edge2.weight = c;
// 		edge2.adjver = a;
// 		edge2->next = sites[b].first_edge;
// 		sites[a].first_edge = edge2;
// 	}

// }