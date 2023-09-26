#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int time;
//求图中的各强连通分量的算法
/*
 * 思想是先用原图做一遍DFS,把所有点的完成时间计算出来,再把图反向
 * 之后按照结点完成时间从大到小的顺序对转置图做DFS，用一个数组保存结点
 * 用邻接矩阵存储,两遍dfs: O(V^2) 矩阵转置: O(V^2), 所以总的时间复杂度O(V^2)
 */
class Node{
public:
    int d;      // 开始时间
    int f;      // 结束时间
    int color;
    Node() : d(0), f(0), color(0) {}
};


void DFS_VISIT(vector<Node> &V, vector<vector<int>> &E, int k);

inline bool cmp(pair<int, int> &x, pair<int, int> &y) {return x.second > y.second;}

void DFS(vector<Node> &V, vector<vector<int>> &E)
{
    // 图用邻接矩阵存储
    time = 0;
    for(int i = 0; i < V.size(); ++i)
    {
        if(V[i].color == 0)
        {
            DFS_VISIT(V, E, i);
        }
    }
}

void DFS_VISIT(vector<Node> &V, vector<vector<int>> &E, int k)
{
    // 计算访问开始时间和访问结束时间
    time = time + 1;
    V[k].color = 1;
    V[k].d = time;
    // O(E)
    for(int i = 0; i < E.size(); ++i)
    {
        if(E[k][i] == 1 && V[i].color == 0)
        {
            DFS_VISIT(V, E, i);
        }
    }
    // 结束访问
    time = time + 1;
    V[k].f = time;
}


void DFS_VISIT_toFIND_COMPONENT(vector<int> &component, vector<Node> &V, vector<vector<int>> &E, int k)
{
    component.push_back(k);
    V[k].color = 1;
    for(int i = 0; i < E.size(); ++i)
    {
        if(E[k][i] == 1 && V[i].color == 0)
        {
            DFS_VISIT_toFIND_COMPONENT(component, V, E, i);
        }
    }
}

inline void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void TRANSPOSE(vector<vector<int>> &E)
{
    // O(E^2)
    for(int i = 0; i < E.size(); ++i)
    {
        for(int j = i + 1; j < E.size(); ++j)
            swap(E[i][j], E[j][i]);
    }
}


void GRAPH_PRINT(vector<vector<int>> &E)
{
    for(int i = 0; i < E.size(); ++i)
    {
        for(int j = 0; j < E.size(); ++j)
            cout << E[i][j] << " ";
        cout << endl;
    }
}

void FIND_STRONG_CONNECTED_COMPONENT(vector<Node> &positiveDFS_V, std::vector<vector<int>> &Et, vector<Node> &Vp)
{
    vector<int> component;
    vector<pair<int, int>> farray(positiveDFS_V.size());
    for(int i = 0; i < positiveDFS_V.size(); ++i)
        farray[i] = {i, positiveDFS_V[i].f};
    sort(farray.begin(), farray.end(), cmp);	//按照结点完成时间的从大到小进行排序
    for(int i = 0; i < farray.size(); ++i)
    {
        if(Vp[farray[i].first].color == 0)
        {
            DFS_VISIT_toFIND_COMPONENT(component, Vp, Et, farray[i].first);
            cout << "Strongly-Connected-Component :";
            for(int j = 0; j < component.size(); ++j)
            {
                cout << component[j] << "  ";
            }
            cout << endl;
            component.clear();
        }
    }
}

//邻接矩阵表示图
int main(void)
{
    cout << "enter the number of vertex:";
    int tmp;
    cin >> tmp;
    vector<Node> V(tmp);
    vector<vector<int>> E(tmp, vector<int>(tmp, 0));
    while(true)
    {
        cout << "Please enter two adjacent points: ";
        int x, y;
        cin >> x >> y;
        if(x == -1 && y == -1)
            break;
        E[x][y] = 1;
    }
    GRAPH_PRINT(E);
    DFS(V, E);

    time = 0;
    cout << endl;
    vector<Node> Vp(V.size());
    TRANSPOSE(E);
    GRAPH_PRINT(E);
    FIND_STRONG_CONNECTED_COMPONENT(V, E, Vp);
    return 0;
}
/*
0 1
1 2
1 4
1 3
2 5
3 0
3 4
4 5
5 4
-1 -1
*/

/*
0 1
0 2
1 3
2 3
3 0
2 4
3 5
4 5
-1 -1
*/