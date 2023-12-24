#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
	int val;
	Node * left;
	Node * right;
	Node * father;
	Node(int value) : left(NULL), right(NULL), val(value) {}
};

class BST{
public:
	Node * root;
	void insert(int val);
	BST() : root(NULL) {}
	void inOrder();
	void inOrder(Node * node);
	int find(int val);
};

void BST::inOrder(){
	if(root){
		inOrder(root);
	}
}

int BST::find(int val){
	if(!root){
		return 0;
	}
	queue<Node*> que;
	que.push(root);
	int h = 1;
	int count = 1;
	while(!que.empty()){
		Node * tmp = que.front();
		que.pop();
		if(tmp->val == val){
			return h;
		}
		if(tmp->left){
			que.push(tmp->left);
		}
		if(tmp->right){
			que.push(tmp->right);
		}
		if(!--count){
			count = que.size();
			++h;
		}
	}
	return 0;
}

void BST::inOrder(Node * node){
	if(node->left){
		inOrder(node->left);
	}
	cout << node->val << " ";
	if(node->right){
		inOrder(node->right);
	}
}

void BST::insert(int val){
	Node * node = new Node(val);
	if(!root){
		root = node;
		return ;
	}
	Node * p = root;
	Node * f = NULL;
	while(p){
		if(val < p->val){
			f = p;
			p = p->left;
		}
		else if(val == p->val){
			cout << "Existing value:" << val << endl;
			return;
		}
		else{
			f = p;
			p = p->right;
		}
	}
	if(val > f->val){
		f->right = node;
		node->father = f;
	}
	else{
		f->left = node;
		node->father = f;
	}
}

int main(){
	BST * bst = new BST();
	int n;
	cout << "enter the number of vertices: ";
	cin >> n;
	vector<int> arr(n);
	for(int i = 0; i < arr.size(); ++i){
		cout << "enter the value: ";
		cin >> arr[i];
		// cout << arr[i] << endl;
		bst->insert(arr[i]);
	}
	// cout << "root" << " " << bst->root->val << endl;
	bst->inOrder();
	cout << endl;
	for(int i = 0; i < arr.size(); ++i){
		int h = bst->find(arr[i]);
		if(h == 0)
			continue;
		cout << arr[i] << ": " << h << endl;
	}
	int val;
	cout << "enter the value you want to insert: ";
	cin >> val;
	bst->insert(val);
	cout << "enter the value you want to find: ";
	cin >> val;
	cout << bst->find(val) << endl;
	bst->inOrder();
	return 0;
}

/*
7
1
0
-2
3
2
4
6
*/
