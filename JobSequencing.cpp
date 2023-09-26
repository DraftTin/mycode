#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
	int number; // 表示容纳作业的编号 0表示无
	int parent; // 小于0表示为根节点  大于零表示父节点的编号
	Node() : parent(-1), number(0) {}
};

class Job{
public:
	int p;
	int d;
	int number;
};

void sort(vector<Job>& arr, int begin, int end){
	if(begin >= end) return ;
	int i = begin;
	int j = end;
	Job mid = arr[begin];
	while(i < j){
		while(i < j && arr[j].p <= mid.p){
			--j;
		}
		arr[i] = arr[j];
		while(i < j && arr[i].p >= mid.p){
			++i;
		}
		arr[j] = arr[i];
	}
	arr[i] = mid;
	sort(arr, begin, i);
	sort(arr, i + 1, end);
}

int find(vector<Node>& nodeSet, int i){
	if(nodeSet[i].parent >= 0){
		nodeSet[i].parent = find(nodeSet, nodeSet[i].parent);
		i = nodeSet[i].parent;
	}
	return i;
}

void Union(vector<Node>& nodeSet, int i, int j) {
	int lroot = find(nodeSet, i);
	int rroot = find(nodeSet, j);
	//cout << -nodeSet[lroot].parent << " " << -nodeSet[rroot].parent << endl;
	if(-nodeSet[lroot].parent >= -nodeSet[rroot].parent){
		nodeSet[lroot].parent += nodeSet[rroot].parent;
		nodeSet[rroot].parent = lroot;
	}
	else {
		nodeSet[rroot].parent += nodeSet[lroot].parent;
		nodeSet[lroot].parent = rroot;
	}
}



vector<Node> solution(vector<Job>& jobs){
	sort(jobs, 0, jobs.size() - 1);
	vector<Node> nodeSet(jobs.size() + 1);
	vector<int> F(jobs.size() + 1); // 表示在节点i前距节点i最近的空位，如果值为0则表示没有符合条件的节点
	for(int i = 0; i < F.size(); ++i){
		F[i] = i;
	}
	cout << 0 << ": ";
	for(int j = 0; j < nodeSet.size(); ++j){
		cout << nodeSet[j].parent << " ";
	}
	cout << endl;

	for(int i = 0; i < jobs.size(); ++i){
		int index = jobs.size() > jobs[i].d ? jobs[i].d : jobs.size();
		int tmp = find(nodeSet, index);	// 找到该集合的根节点
		int pos = F[tmp];		// 找到距该树最近的空闲节点，若存在，则将空闲区放置该作业，并将该树和前一个树合并成新树，修改原树根的F值
		if(pos != 0){
			nodeSet[pos].number = jobs[i].number;	// 
			int l = find(nodeSet, pos - 1);
			Union(nodeSet, l, tmp);	// 用l-1和tmp合并的原因是tmp为原树根，而tmp-1未必是上一棵树，用pos-1可以保证是上一颗树
			F[tmp] = F[l];
		}
		cout << i + 1 << ": ";
		for(int j = 0; j < nodeSet.size(); ++j){
			cout << nodeSet[j].parent << " ";
		}
		cout << endl;
	}
	return nodeSet;
}

int main(){
	vector<Job> jobs;
	int n;
	cin >> n;	
	for(int i = 0; i < n; ++i){
		int p, d;
		cin >> p >> d;
		jobs.push_back({p, d, i + 1});
	}
	vector<Node> nodeSet = solution(jobs);
	cout << "##: " << endl;
	for(int i = 1; i < nodeSet.size(); ++i){
		cout << nodeSet[i].number << " ";
	}
	cout << endl;
 	return 0;
}

/*
7
40 2
12 4
30 4
20 3
7 2
15 1
10 6
*/

/*
7
35 4
30 2
25 4
20 3
15 4
10 8
5 3
*/