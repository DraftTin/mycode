#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
	Node * left;
	Node * right;
	Node * father;
	int val;
	explicit Node(int value) : father(NULL), left(NULL), right(NULL), val(value) {}
};

// 二叉搜索树
class BST{
public:
	Node * root;
	void init();
	Node * Minimum(Node * node);
	Node * Maximum(Node * node);
	Node * successor(Node * node);
	Node * precessor(Node * node);
	Node * find(int val);
	//void preOrder();
	void nodesGreaterThanVal(Node * node, int val, vector<int>& res);
	void removeNodesGreaterThanVal(int val);
	void inOrder();
	void levelOrder();
	void insert(int val);
	void remove(int val);
	void replace(Node * n1, Node * n2);
	BST() : root(NULL) {}
private:
	void inOrder(Node * node);
};

void BST::nodesGreaterThanVal(Node * node, int val, vector<int>& res){
	if(node == NULL) return ;
	if(node->val >= val) res.push_back(node->val);
	nodesGreaterThanVal(node->left, val, res);
	nodesGreaterThanVal(node->right, val, res);
}

void BST::removeNodesGreaterThanVal(int val){
	// 删除所有大于val的结点，遍历存储O(V), 每次调用remove函数O(logV)，假设数据分布均匀，val随机，则平均调用(V/2)次，总的时间复杂度O(Vlog(V))
	vector<int> res;
	nodesGreaterThanVal(root, val, res);
	if(res.empty()){ return ;}
	for(int tmp : res){
		remove(tmp);
	}
}

Node * BST::Maximum(Node * node){
	if(node == NULL)
		return NULL;
	Node * p = node;
	while(p->right){
		p = p->right;
	}
	return p;
}

Node * BST::successor(Node * node){
	// 寻找结点node的后继，若有右子树则返回右子树的中序初始结点即右子树最小的结点
	if(node == NULL)
		return NULL;
	if(node->right)
		return Minimum(node->right);
	// 若没有右子树，则向上查询直到搜索到根节点或该节点是其父节点的左孩子，搜索到根节点则说明没有后继，否则后继是其父节点
	while(node->father && node == node->father->right){
		node = node->father;
	}
	return node->father;
}

Node * BST::precessor(Node * node){
	if(node == NULL)
		return NULL;
	if(node->left)
		return Maximum(node->left);
	while(node->father && node == node->father->left){
		node = node->father;
	}
	return node->father;
}

Node * BST::Minimum(Node * node){
	// 返回该树的中序首结点即最小的结点
	if(node == NULL)
		return NULL;
	Node * p = node;
	while(p->left){
		p = p->left;
	}
	return p;
}

void BST::inOrder(){
	inOrder(root);
}

void BST::inOrder(Node * node){
	if(!node)
		return ;
	inOrder(node->left);
	cout << node->val << endl;
	inOrder(node->right);
}

void BST::replace(Node * n1, Node * n2){
	// 用n2替换n1的位置，只处理n2和n1父节点之间的关系
	if(n1->father == NULL){
		root = n2;  
	}
	else if(n1 == n1->father->left){
		n1->father->left = n2;
	}
	else{
		n1->father->right = n2;
	}
	if(n2 != NULL){
		n2->father = n1->father;
	}
}

Node * BST::find(int val){
	Node * p = root;
	while(p){
		if(val > p->val)
			p = p->right;
		else if(val < p->val)
			p = p->left;
		else
			return p;
	}
	return NULL;
}

void BST::remove(int val){
	// 若没有左子树则用右子树代替该结点, 若没有右子树则用左子树代替该结点, 若左右子树均存在, 则找到右子树最小结点和该节点交换
	Node * node = find(val);
	Node * p = NULL;
	if(node == NULL)
		return	 ;
	if(node->left == NULL){
		replace(node, node->right);
	}
	else if(node->right == NULL){
		replace(node, node->left);
	}
	else{
		p = Minimum(node->right);
		if(p->father != node){
			replace(p, p->right);
			p->right = node->right;
			p->right->father = p;
		}
		replace(node, p);
		p->left = node->left;
		p->left->father = p;
	}	
}

void BST::init(){
	if(root){
		cout << "the tree has been modified" << endl;
		return ;
	}
	int val;
	while(true){
		cout << "enter the val: ";
		cin >> val;
		if(val == -1)
			break;
		insert(val);
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
			cout << "Existing value" << endl;
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

void BST::levelOrder(){
	queue<Node*> que;
	if(root == NULL) return ;
	int count = 0;
	que.push(root);
	++count;
	while(!que.empty()){
		Node * tmp = que.front();
		cout << tmp->val << " ";
		que.pop();
		if(tmp->left){
			que.push(tmp->left);
		}
		if(tmp->right){
			que.push(tmp->right);
		}
		if(!--count){
			cout << endl;
			count = que.size();
		}
	}
}

int levelOfNode(Node * root, int val, int level){
	// 查找结点的层次
	if(!root) return -1;
	if(root->val == val) return level;
	return max(levelOfNode(root->left, val, level + 1), levelOfNode(root->right, val, level + 1));
}

int main(){
	BST * bst = new BST();
	bst->init();
	bst->levelOrder();
	int level = levelOfNode(bst->root, 100, 0);
	cout << endl;
	cout << level << endl;
	return 0;
}

/*17 31 13 11 20 35 25 8 4 11 24 40 27*/