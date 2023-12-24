#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
	char val;
	Node *Bigchild;
	Node *nextBrother;
	Node(char v) : val(v), Bigchild(NULL), nextBrother(NULL) {}
};

class Tree{
public:
	Node *root;
	void CreatTree();
	void preOrder_Create();
	//Node *FindFather(Node *node);
	//void DeleteSubtree(Node *node); //删除子树, 并调整树中受影响结点的位置
	void preOrder_traversal();
	void height(Node *node, int h, int& maxh);
private:
	void preOrder_traversal(Node *node);
	Node * preOrder_Create(char val);
	void Delete(Node *node); //释放子树的空间
};

void cTree(char *data, int *degree, int n){
    vector<Node*> nodes(n); 
    for(int i = 0; i < n; ++i){
    	nodes[i] = new Node(data[i]);
    }
    int next = 0;
    next += 1;
    for(int i = 0; i < n; ++i){
    	int d = degree[i];
    	//cout << degree[i] << endl;
    	if(d != 0){
    		nodes[i]->Bigchild = nodes[next]; //指向大儿子结点
    		Node *p = nodes[i]->Bigchild;
    		++next;
    		for(int j = 2; j <= d; ++j){
    			p->nextBrother = nodes[next++];
    			p = p->nextBrother;
    		}
    		p->nextBrother = NULL;
    		//next = next - d;
    	}
    }
    Tree tree;
    tree.root = nodes[0];
    tree.preOrder_traversal();
}

Node * Tree::preOrder_Create(char val){
	if(val == '0') return NULL;
	Node * node = new Node(val);
	cin >> val;
	node->Bigchild = preOrder_Create(val);
	cin >> val;
	node->nextBrother = preOrder_Create(val);
	return node;
}

void Tree::preOrder_Create(){
	char val;
	cin >> val;
	root = preOrder_Create(val);
}

void Tree::preOrder_traversal(){
	if(root == NULL){
		cout << "empty tree" << endl;
		return ;
	}
	preOrder_traversal(root);
}


void Tree::height(Node *node, int h, int& maxh){
	if(node == NULL)
		return ;
	if(h > maxh)
		maxh = h;
	height(node->nextBrother, h, maxh);
	height(node->Bigchild, h + 1, maxh);
}

void Tree::preOrder_traversal(Node *node){
	if(node == NULL)
		return ;
	cout << node->val << endl;
	preOrder_traversal(node->Bigchild);
	preOrder_traversal(node->nextBrother);
}

void Tree::CreatTree(){
	cout << "enter the root val: ";
	char val;
	cin >> val;
	if(val == '#')
		return ;
	root = new Node(val);
	queue<Node*> que;
	que.push(root);
	while(!que.empty()){
		Node *tmp = que.front();
		que.pop();
		cout << "enter the bigchild val:";
		cin >> val;
		if(val != '#'){
			tmp->Bigchild = new Node(val);
			que.push(tmp->Bigchild);
			cout << "enter the other child val and enter # to stop:" <<  endl;
			Node *p = tmp->Bigchild;
			while(true){
				cout << "enter the val:";
				cin >> val;
				if(val == '#')
					break;
				p->nextBrother = new Node(val);
				que.push(p->nextBrother);
				p = p->nextBrother;
			}
		}
	}
}

void Tree::Delete(Node *node){
	if(node == NULL)
		return ;
	Node *child = node->Bigchild;
	while(child != NULL){
		Node *tmp = child->nextBrother;
		Delete(child);
		child = tmp;
	}
	delete node;
}

// Node * Tree::FindFather(Node *node){
// 	if(root == NULL)
// 		return NULL;
// 	queue<Node*> que;
// 	que.push(root);
// 	while(!que.empty()){
// 		Node *tmp = que.front();
// 		que.pop();
// 		if(tmp->left == node || tmp->right == node)
// 			return tmp;
// 		if(tmp->left)
// 			que.push(tmp->left);
// 		if(tmp->right)
// 			que.push(tmp->right);
// 	}
// 	return NULL;
// 	//复杂度O(n)
// }

int main(void){
	Tree tree;
	tree.preOrder_Create();
	tree.preOrder_traversal();
	int h = 1;
	tree.height(tree.root, h, h);
	cout << "h = " << h << endl;
	// int n;
	// cin >> n;
	// char *data = new char[n];
	// for(int i = 0; i < n; ++i){
	// 	cout << "data: ";
	// 	cin >> data[i];
	// }
	// int *degree = new int[n];
	// for(int i = 0; i < n; ++i){
	// 	cout << "degree: ";
	// 	cin >> degree[i];
	// }
	// cTree(data, degree, n);
	return 0;
}

/*
12
A
B
C
D
E
F
G
H
I
K
L
J
3
2
1
2
3
0
0
0
0
0
0
0
*/