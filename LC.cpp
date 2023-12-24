#include <iostream>
#include <vector>

using namespace std;

class Job{
public:
    int p;
    int t;
    int d;
};
class Node{
public:
    vector<int> index;
    int maxIndex;
    int u;  // 罚款的上限
    int c;  // 罚款的下限
    bool canAdd(vector<Job>& jobs, int k);
    Node() : maxIndex(-1), u(0), c(0) {}
};
bool Node::canAdd(vector<Job>& jobs, int k){
    index.push_back(k);
    vector<int> visited(index.size(), 0);
    int mark = 0;
    for(int i = 0; i < index.size(); ++i){
        int mindeadline = INT_MAX;
        int minI = -1;
        for(int j = 0; j < index.size(); ++j){
            if(!visited[j] && jobs[index[j]].d < mindeadline){
                mindeadline = jobs[index[j]].d;
                minI = j;
            }
        }
        visited[minI] = 1;
        mark += jobs[index[minI]].t;
        if(mark > jobs[index[minI]].d){
            index.pop_back();
            return false;
        }
    }
    index.pop_back();
    return true;
}

void solution(vector<Job>& jobs, Node T, vector<Node>& list, int& U, Node& minNode){
    // 算法LC检索  带有期限的作业排序问题
    // T表示当前节点  list表示当前的活结点表 U表示当前记录下的最小的代价值  minNode记录下最优解
    for(int i = T.maxIndex + 1; i < jobs.size(); ++i){
        if(T.canAdd(jobs, i)){
            int u = T.u - jobs[i].p;
            int c = T.c;
            for(int j = T.maxIndex + 1; j < i; ++j){
                c += jobs[j].p;
            }
            if(c >= U) continue;
            Node tmp = T;
            tmp.index.push_back(i);
            tmp.u = u;
            tmp.c = c;
            tmp.maxIndex = i;
            list.push_back(tmp);
            if(tmp.u < U){
                U = tmp.u;
                minNode = tmp;
            }
        }
    }
    if(list.empty() == true) {
        cout << "The min cost: " << U << endl;
        cout << "set: ";
        for(int i = 0; i < minNode.index.size(); ++i){
            cout << minNode.index[i] + 1 << " ";
        }
        cout << endl;
        return ;
    }
    int minIndex = -1;
    int minCVal = INT_MAX;
    for(int i = 0; i < list.size(); ++i){
        if(list[i].c < minCVal){
            minCVal = list[i].c;
            minIndex = i;
        }
    }
    Node node = list[minIndex];
    list.erase(list.begin() + minIndex);
    solution(jobs, node, list, U, minNode);
}

int main(){
    vector<Job> jobs;
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i){
        int p, t, d;
        cin >> p >> d >> t;
        jobs.push_back({p, t, d});
    }
    vector<Node> list;
    int U = INT_MAX;
    Node T;
    for(int i = 0; i < jobs.size(); ++i){
        T.u += jobs[i].p;
    }
    // T.index.push_back(0);
    solution(jobs, T, list, U, T);
    return 0;
}