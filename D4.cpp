#include <iostream>

using namespace std;

const int MAX = 109;

class Node{
public:
	int val;
	Node * father;
	Node *Bigchild;
	Node *nextBrother;
	Node(int v) : val(v), Bigchild(NULL), nextBrother(NULL), father(NULL) {}
};

class Tree{
public:
	Node *root;
	void preOrder_Create();
private:
	Node * preOrder_Create(int val, Node * father);
};

Node * Tree::preOrder_Create(int val, Node * father){
	if(val == 0) return NULL;
	Node * node = new Node(val);
	node->father = father;
	cin >> val;
	node->Bigchild = preOrder_Create(val, node);
	cin >> val;
	node->nextBrother = preOrder_Create(val, father);
	return node;
}

void Tree::preOrder_Create(){
	int val;
	cin >> val;
	root = preOrder_Create(val, NULL);
}


void dfs(Node * cur_node, int cur_max, int cur_min, int& maxVal, int max_path[], int& len){
	// 求到当前点路径乘积最大值 cur_max和cur_min表示当前层上层最大乘积和最小乘积  maxVal表示整棵树的最大乘积
	// path记录maxVal对应的最长路径
	if(cur_node == NULL) return;
	int val = cur_node->val;
	int tmp_max = cur_max;
	int tmp_min = cur_min;
	if(val < 0){
		int tmp = tmp_max;
		tmp_max = cur_min;
		tmp_min = tmp;
	}
	tmp_max = max(val, tmp_max * val);
	tmp_min = min(val, tmp_min * val);
	
	if(tmp_max > maxVal){
		maxVal = tmp_max;
		int i = 0;
		Node * tmp = cur_node->father;
		int tmp_val = val;
		max_path[i++] = cur_node->val; // i == 1
		while(tmp_val != tmp_max){
			tmp_val *= tmp->val;
			max_path[i++] = tmp->val;
			tmp = tmp->father;
		}
		len = i;
		for(int v1 = 0, v2 = len - 1; v1 < v2; ++v1, --v2){
			int tmp = max_path[v1];
			max_path[v1] = max_path[v2];
			max_path[v2] = tmp;
		}
	}
	dfs(cur_node->Bigchild, tmp_max, tmp_min, maxVal, max_path, len);
	dfs(cur_node->nextBrother, cur_max, cur_min, maxVal, max_path, len);
}


void solution(Tree& tree){
	int max_path[MAX];
	int len = 0;
	Node * root = tree.root;
	int maxVal = -99999;
	dfs(root, 1, 1, maxVal, max_path, len);
	cout << maxVal << endl;
	for(int i = 0; i < len - 1; ++i){
		cout << max_path[i] << " ";
	}
	cout << max_path[len - 1];
}

int main(void){
	//5 1 2 0 0 6 0 2 0 0 3 4 2 0 0 0 7 0 0 0
	Tree tree;
	tree.preOrder_Create();
	solution(tree);
	return 0;
}
