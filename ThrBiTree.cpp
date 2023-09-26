#include <iostream>
#include <queue>

using namespace std;

// 线索二叉树: 创建, 线索化, 遍历
// 创建: 层次创建 + 线索化
// 线索化: 头节点左标签为0 (方便遍历), 为二叉树根节点, 右标签为1, 为中序遍历最后一个结点, 在遍历的时候, 若结点的左或右结点为空, 则赋值中序前继和后继结点
// 遍历: 从二叉树的中序第一个结点开始, 输出该结点,若右标签为1, 则后继节点为右子树, 否则重复上述过程
class TBNode{
public:
	int ltag;
	int rtag;
	TBNode * left;
	TBNode * right;
	int val;
	TBNode(int v) : val(v), left(NULL), right(NULL), ltag(0), rtag(0) {}
};

class TBTree{
public:
	TBNode * head;
	void createTBTree();
	void inOrderTraverse();
	void inOrderThreading();
	void preOrderThreading();
	void preOrderTraverse();
	void postOrderThreading();
	void postOrderTraverse();
	TBTree() : head(new TBNode(0)) {
		head->rtag = 1;
		head->right = head;
	}
private:
	void postThreading(TBNode * node, TBNode *& pre);
	void preThreading(TBNode * node, TBNode *& pre);
	void inThreading(TBNode * node, TBNode *& pre);
};


TBNode * FIRST(TBNode * node){
	while(node->ltag == 0){
		node = node->left;
	}
	return node;
}

TBNode * NEXT(TBNode * node){
	if(node->rtag == 0){
		return FIRST(node->right);
	}
	else{
		return node->right;
	}
}

void TBTree::preOrderTraverse(){
	for(TBNode * tmp = head->left; tmp != head; tmp = tmp->right){
		while(tmp != head && tmp->ltag == 0){
			cout << tmp->val << endl;
			tmp = tmp->left;
		}
		cout << tmp->val << endl;
	}
}

void TBTree::preOrderThreading(){
	TBNode * pre = head;
	preThreading(head->left, pre);
	head->right = pre;
	head->rtag = 1;
	pre->rtag = 1;
	pre->right = head;
} 

void TBTree::preThreading(TBNode * node, TBNode *& pre){
	if(!node->left){
		node->ltag = 1;
		node->left = pre;
	}
	if(!pre->right){
		pre->rtag = 1;
		pre->right = node;
	}
	pre = node;
	if(node->left && node->ltag == 0){
		preThreading(node->left, pre);
	}
	if(node->right && node->rtag == 0){
		preThreading(node->right, pre);
	}
}

void TBTree::createTBTree(){
	if(head->left){
		cout << "existing tree" << endl;
		return ;
	}
	cout << "enter val: ";
	int val;
	cin >> val;
	if(val == 0)
		return ;
	head->left = new TBNode(val);
	queue<TBNode*> que;
	que.push(head->left);
	while(!que.empty()){
		TBNode * tmp = que.front();
		que.pop();
		cout << "enter the val of left child:";
		cin >> val;
		if(val != 0){
			tmp->left = new TBNode(val);
			que.push(tmp->left);
		}
		cout << "enter the val of right child:";
		cin >> val;
		if(val != 0){
			tmp->right = new TBNode(val);
			que.push(tmp->right);
		}
	}
	// inOrderThreading();
}

void TBTree::inOrderThreading(){
	TBNode * pre = head;
	head->ltag = 0;
	// head->left为二叉树的根节点
	inThreading(head->left, pre);
	head->right = pre;
	pre->rtag = 1;
	pre->right = head;
}

/*
void TBTree::inThreading(TBNode * node, TBNode *& pre){
	if(!node) return ;
	inThreading(node->left, pre);
	if(!node->left){
		node->ltag = 1;
		node->left = pre;
	}
	if(!pre->right){
		pre->rtag = 1;
		pre->right = node;
	}
	pre = node;
	inThreading(node->right, pre);
}
*/

void TBTree::inThreading(TBNode * node, TBNode *& pre){
	if(node->left){
		inThreading(node->left, pre);
	}
	else{
		node->ltag = 1;
		node->left = pre;
	}
	if(!pre->right){
		pre->rtag = 1;
		pre->right = node;
	}
	pre = node;
	if(node->right){
		inThreading(node->right, pre);
	}
}

void TBTree::inOrderTraverse(){
	for(TBNode * tmp = FIRST(head); tmp != head; tmp = NEXT(tmp)){
		cout << tmp->val << endl;
	}
}

int main(){
	TBTree * tbtree = new TBTree();
	tbtree->createTBTree();
	tbtree->preOrderThreading();
	tbtree->preOrderTraverse();
	return 0;
}