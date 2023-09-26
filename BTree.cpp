#include <bits/stdc++.h>

using namespace std;

class Node{
public:
	char val;
	Node * left;
	Node * right;
	Node * pre;
	Node(int v) : left(NULL), right(NULL), pre(NULL), val(v) {}
	Node() : left(NULL), right(NULL), pre(NULL) {}
	~Node() {}
};

class Tree{
public:
	Tree() : root(NULL) {}
	~Tree();
	void CreateBT();
	void CreateBTByPreOrder();
	void LevelOrder();
	void inOrder();
	void inOrderWithoutRecursion();
	void preOrderWithoutRecursion();
	void postOrderWithoutRecursion();
	int Height();
	void Delete(Node *node);
	void printLongestPath_bfs();
	void printLongestPath_dfs();
	bool isCompleteBinaryTree();
private:
	void printLongestPath_dfs(Node * node, vector<Node*>& path, vector<Node*>& maxPath, int& length, int& maxlength);
	Node *printLongestPath_bfs(Node * node, int h);
	Node * CreateBTByPreOrder(char val);
	void CreateBT(Node * node);
	void inOrder(Node * node);
public:
	Node * root;	
};

Tree::~Tree() {Delete(root);}


void Tree::printLongestPath_dfs(){
	if(!root) return ;
	vector<Node*> path(1024);
	vector<Node*> maxPath(1024);
	int length = 1;
	int maxlength = 1;
	printLongestPath_dfs(root, path, maxPath, length, maxlength);
	maxPath[0] = root;
	for(int i = 0; i < maxlength; ++i){
		cout << maxPath[i]->val << endl;
	}
}

// 输出二叉树最长路径，dfs，输出路径的常用手法
void Tree::printLongestPath_dfs(Node * node, vector<Node*>& path, vector<Node*>& maxPath, int& length, int& maxlength){
	if(node->left){
		path[length] = node->left;
		++length;
		printLongestPath_dfs(node->left, path, maxPath, length, maxlength);
		--length;
	}
	if(node->right){
		path[length] = node->right;
		++length;
		printLongestPath_dfs(node->right, path, maxPath, length, maxlength);
		--length;
	}
	if(length > maxlength){
		maxlength = length;
		maxPath = path;
	}
}

Node *Tree::printLongestPath_bfs(Node *node, int h){
	if(h == Height())
		return node;
	Node *left = NULL;
	Node *right = NULL;
	if(node->left)
		left = printLongestPath_bfs(node->left, h + 1);
	if(node->right)
		right = printLongestPath_bfs(node->right, h + 1);
	else if(!node->left && !node->right)
		return NULL;
	return left == NULL ? right : left;
}

void Tree::printLongestPath_bfs(){
	if(root == NULL)
		return ;
	Node *node = printLongestPath_bfs(root, 1);
	Node *tmp = node;
	vector<char> path;
	while(tmp){
		path.push_back(tmp->val);
		tmp = tmp->pre;
	}
	for(int i = path.size() - 1; i >= 0; --i)
		cout << path[i] << endl;
}

bool Tree::isCompleteBinaryTree(){
	if(root == NULL)
		return true;
	queue<Node*> que;
	que.push(root);
	int flag = 0;
	while(!que.empty()){
		Node *tmp = que.front();
		que.pop();
		if(tmp->left){
			if(flag == 1)
				return false;
			que.push(tmp->left);
		}
		else
			flag = 1;
		if(tmp->right){
			if(flag == 1)
				return false;
			que.push(tmp->right);
		}
		else
			flag = 1;
	}
	return true;
}

void Tree::Delete(Node *node){
	if(node == NULL)
		return ;
	if(node->left)
		Delete(node->left);
	if(node->right)
		Delete(node->right);
	delete node;
}

int Tree::Height(){
	if(root == NULL)
		return 0;
	queue<Node*> que;
	que.push(root);
	int num = 1;
	int height = 0;
	while(!que.empty()){
		Node *tmp = que.front();
		que.pop();
		if(tmp->left)
			que.push(tmp->left);
		if(tmp->right)
			que.push(tmp->right);
		if(!--num){
			num = que.size();
			++height;
		}
	}
	return height;
}

void Tree::LevelOrder(){
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
		//每个结点出队入队一次, O(n)
		if(!--count){
			count = que.size();
			cout << endl;
		}
	}
}

void Tree::CreateBT(Node * node){
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
			tmp->left->pre = tmp;
		}
		cout << "enter the val:" << endl;
		cin >> val;
		cin.ignore(1024, '\n');
		if(val != '#'){
			tmp->right = new Node(val);
			que.push(tmp->right);
			tmp->right->pre = tmp;
		}
	}
}

void Tree::CreateBT() {
	if(root != NULL){
		cout << "BT has been created." << endl;
		return ;
	}
	cout << "enter the val:";
	char val;
	cin >> val;
	if(val != '#'){
		root = new Node(val);
		CreateBT(root);
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
	// 非递归中序遍历
	stack<Node*> sta;
	Node *p = root;
	while(!sta.empty() || p){
		while(p){
			sta.push(p);
			p = p->left;
		}
		p = sta.top();
		cout << p->val << endl;
		sta.pop();
		p = p->right;
	}
}


void Tree::preOrderWithoutRecursion(){
	// 非递归前序遍历
	// 一直向左遍历，若无左子树，赋值为栈顶的右子树继续上述过程，直到栈空
	stack<Node*> sta;
	Node *p = root;
	while(!sta.empty() || p){
		while(p){
			cout << p->val << " ";
			sta.push(p);
			p = p->left;
		}
		p = sta.top();
		p = p->right;
		sta.pop();
	}
	cout << endl;
}


void Tree::postOrderWithoutRecursion(){
	// 非递归后序遍历
    // 每次循环取栈顶的元素但不出栈，如果结点左右子树为空或左右子树都被访问过，则输出这个结点，并弹栈，将弹出的结点赋给pre指针，判断左右子树是否被访问过的方法就是判断pre == p->left || pre == p->right, 
	// 这个条件说明左或右子树被访问过，又由于p这个结点被访问，所以左右子树一定均被访问完成了，不然栈顶元素不可能是这个结点。
	stack<Node*> sta;
	Node *p = root;
	Node * pre = NULL;
	sta.push(root);
	while(!sta.empty()){
		p = sta.top();
		if((!p->left && !p->right) || (pre != NULL && (p->left == pre || p->right == pre))){
			cout << p->val << " ";
			pre = p;
			sta.pop();
		}
		else{
			if(p->right) sta.push(p->right);
			if(p->left) sta.push(p->left);
		}
	}
	cout << endl;
}

bool judgeBST(Node * root, int minval, int maxval){
	// 此处的val是int类型的，结点中的数据是char类型，但算法是正确的
	if(root == NULL) return true;
	if(root->val > minval && root->val < maxval){
		return judgeBST(root->left, minval, root->val) && judgeBST(root->right, root->val, maxval);
	}
	return false;	
}

bool isSimilar(Node * t1, Node * t2){
	// 判断两个二叉树是否相似
	if(t1 && t2) return isSimilar(t1->right, t2->right) && isSimilar(t1->left, t2->left);
	else if(t1 || t2) return false;
	else return true;
}

int numberOfleafOnLevel(Node * root, int level){
	// 判断二叉树某层有多少个叶结点
	if(!root) return 0;
	if(level == 0){
		return !root->right && !root->left ? 1 : 0;
	}
	queue<Node*> que;
	int count = 0;
	que.push(root);
	++count;
	int height = 0;
	while(!que.empty()){
		Node * tmp = que.front();
		que.pop();	
		if(tmp->left) que.push(tmp->left);
		if(tmp->right) que.push(tmp->right);
		if(!--count){
			++height;
			if(height == level){
				int num = 0;
				while(!que.empty()){
					Node * tmp = que.front();
					que.pop();
					if(!tmp->left && !tmp->right){
						++num;
					}
				}
				return num;
			}
			count = que.size();
		}
	}
	return 0;
}

void Tree::CreateBTByPreOrder(){
	if(root) {
		cout << "existed tree" << endl;
		return ;
	}
	cout << "val of root: ";
	char val;
	cin >> val;
	root = CreateBTByPreOrder(val);
}

Node * Tree::CreateBTByPreOrder(char val){
	// 先序创建二叉树
	if(val != '#'){
		Node * node = new Node(val);
		char v;
		cout << "val: ";
		cin >> v;
		node->left = CreateBTByPreOrder(v);
		cout << "val: ";
		cin >> v;
		node->right = CreateBTByPreOrder(v);
		return node;
	}
	return NULL;
}

Node * BTcopy(Node * node){
	if(!node) return NULL;
	Node * root = new Node(node->val);
	root->left = BTcopy(node->left);
	root->right = BTcopy(node->right);
	return root;
}

Node * findParent(Node * root, Node * node){
	if(!root) return NULL;
	queue<Node*> que;
	que.push(root);
	while(!que.empty()){
		Node * tmp = que.front();
		que.pop();
		if(tmp->left){
			if(tmp->left == node) return tmp;
			que.push(tmp->left);
		}
		if(tmp->right){
			if(tmp->right == node) return tmp;
			que.push(tmp->right);
		}
	}
	return NULL;
}

Node * exchangeLeftAndRight(Node * node){
	if(!node) return NULL;
	Node * tmp = node->left;
	node->left = exchangeLeftAndRight(node->right);
	node->right = exchangeLeftAndRight(tmp);
	return node;
}

int num = 0;
void numOfVertices(Node * root){
	if(!root) return ;
	++num;
	numOfVertices(root->left);
	numOfVertices(root->right);
}

int main(void){
	Tree * tree = new Tree();
	// tree->CreateBTByPreOrder();
	tree->CreateBT();
	tree->LevelOrder();
	numOfVertices(tree->root);
	cout << '\n' << num << endl;
	return 0;
} 

/*
1
2
3
4
5
6
#
7
8
#
#
#
#
#
#
#
#
*/

/* 前序创建
2
5
2
#
#
9
#
#
8
5
3
#
#
7
#
#
9
#
#
*/