#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 简单dfs和bfs在图中的应用
void dfs(vector<vector<int>>& graph, vector<int>& visited, int pos, int target, vector<int>& path, int num){
    // 输出从源结点到目标节点的所有路径
    if(pos == target){
        for(int i = 0; i < num; ++i) cout << path[i] << " ";
        cout << endl;
        return ;
    }
    for(int i = 0; i < graph.size(); ++i){
        if(!visited[i] && graph[pos][i]){
            visited[i] = 1;
            path[num] = i;
            dfs(graph, visited, i, target, path, num + 1);
            visited[i] = 0;
        }
    }
}

int bfs(vector<vector<int>>& graph, int root, int k){
    // 求出图中和源结点最近距离为k的节点的数量
    if(k == 0) return 1;
    vector<int> visited(graph.size(), 0);
    queue<int> que;
    int count = 0;
    que.push(root);
    visited[root] = 1;
    ++count;
    int distance = 0;
    while(!que.empty()){
        int tmp = que.front();
        que.pop();
        for(int i = 0; i < graph.size(); ++i){
            if(!visited[i] && graph[tmp][i]){
                que.push(i);
                visited[i] = 1;
            }
        }
        if(!--count){
            ++distance;
            if(distance == k) return que.size();
            count = que.size();
        }
    }
    return 0;
}
/*
5
0 1
0 2
0 3
3 4
-1 -1
0 
2
*/
int main(){
    int n;
    cin >> n;
    // 简化问题，0表示没有边或自身
    vector<vector<int>> graph(n, vector<int>(n, 0));
    while(true){
        cout << "input the edge i <---> j: ";
        int i, j;
        cin >> i >> j;
        if(i == -1 && j == -1) break;
        graph[i][j] = graph[j][i] = 1;
    }
    int root;
    int k;
    cin >> root >> k;
    vector<int> visited(graph.size(), 0);
    vector<int> path(graph.size());
    path[0] = root;
    visited[root] = 1;
    dfs(graph, visited, root, k, path, 1);
    return 0;
}

