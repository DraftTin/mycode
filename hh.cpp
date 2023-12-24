#include <bits/stdc++.h>

using namespace std;

class Node{
public:
	char val;
	Node * left;
	Node * right;
	Node(int v) : left(NULL), right(NULL), val(v) {}
};

class Tree{
public:
	Tree() : root(NULL) {}
	void CreatBT();
	void inOrder();
	void inOrderWithoutRecursion();
private:
	void CreatBT(Node * node);
	void inOrder(Node * node);
	Node * root;
};

void Tree::CreatBT(Node * node){
	queue<Node*> que;
	que.push(node);
	while(!que.empty()){
		Node * tmp = que.front();
		que.pop();
		cout << "enter the val:" << endl;
		char val;
		cin >> val;
		cin.ignore(1024, '\n');
		if(val != '#'){
			tmp->left = new Node(val);
			que.push(tmp->left);
		}
		cout << "enter the val:" << endl;
		cin >> val;
		cin.ignore(1024, '\n');
		if(val != '#'){
			tmp->right = new Node(val);
			que.push(tmp->right);
		}
	}
}

void Tree::CreatBT() {
	if(root != NULL){
		cout << "BT has been created." << endl;
		return ;
	}
	cout << "enter the val:";
	char val;
	cin >> val;
	if(val != '#'){
		root = new Node(val);
		CreatBT(root);
	}
}

void Tree::inOrder(){
	inOrder(root);
}

void Tree::inOrder(Node * node){
	if(node != NULL){
		inOrder(node->left);
		cout << node->val << endl;
		inOrder(node->right);
	}
}

void Tree::inOrderWithoutRecursion(){
	stack<Node*> sta;
	Node * p = root;
	while(!sta.empty() || p){
		while(p){
			sta.push(p);
			p = p->left;
		}
		if(!sta.empty()){
			p = sta.top();
			cout << p->val << endl;
			sta.pop();
			p = p->right;
		}
	}
}

int main(void){
	Tree tree;
	tree.CreatBT();
	tree.inOrderWithoutRecursion();
	return 0;
} 