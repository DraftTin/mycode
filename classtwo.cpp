#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
	Node * left;
	Node * right;
	int val;
	Node(int value) : left(NULL), right(NULL), val(value) {}
};


class BTree{
public:
	Node * root;
	BTree() : root(NULL) {}
	void creatBinaryTree();		//创建二叉树
	void printPath();			//输出路径
	void levelOrder();			//水平遍历
private:
	void dfs(Node * node, vector<Node*> path, int length);  //dfs被printPath()调用
};


void BTree::levelOrder(){
	queue<Node*> que;
	if(root == NULL)
		return ;
	int count = 0;
	que.push(root);
	++count;
	while(!que.empty()){
		Node *tmp = que.front();
		cout << tmp->val << " ";
		que.pop();
		if(tmp->left){
			que.push(tmp->left);
		}
		if(tmp->right){
			que.push(tmp->right);
		}
		if(!--count){
			count = que.size();
			cout << endl;
		}
	}
}

void BTree::dfs(Node * node, vector<Node*> path, int length){
	path.push_back(node);
	for(int i = 0; i < path.size(); ++i){
		cout << path[i]->val << "->";
	}
	cout << "NULL" << "  ";
	cout << "length = " << length << endl;

	if(node->left)
		dfs(node->left, path, length + 1);
	if(node->right)
		dfs(node->right, path, length + 1);
}

void BTree::printPath(){
	if(root == NULL)
		return ;
	vector<Node*> path;
	dfs(root, path, 1);
}


void BTree::creatBinaryTree(){
	if(root != NULL){
		cout << "the tree has been modified" << endl;
		return ;
	}
	cout << "enter the value of root node: ";
	int val;
	cin >> val;
	root = new Node(val);
	queue<Node*> que;
	que.push(root);
	while(!que.empty()){
		Node * tmp = que.front();
		que.pop();
		cout << "enter the left node value or enter 0 to set NULL: ";
		cin >> val;
		if(val != 0){
			Node * left = new Node(val);
			tmp->left = left;
			que.push(left);
		}
		cout << "enter the right node value or enter 0 to set NULL: ";
		cin >> val;
		if(val != 0){
			Node * right = new Node(val);
			tmp->right = right;
			que.push(right);
		}
	}
}

int main(){
	BTree * btree = new BTree();
	btree->creatBinaryTree();
	btree->levelOrder();
	btree->printPath();
	return 0;
}

/*
5 4 0 3 2 1 -1 0 0 0 0 0 
0
*/