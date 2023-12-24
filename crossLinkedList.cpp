#include <iostream>
#include <vector>

using namespace std;

// 循环链表
class Node{
public:
	int row;
	int col;
	int val;
	Node * right;
	Node * down;
	Node(int row_, int col_, int val_) : row(row_), col(col_), val(val_), right(this), down(this) {}
};

class CrossLinkedList{
public:
	vector<Node*> row_head;
	vector<Node*> col_head;
	void createCrossLinkedList();
	void show();
	int m, n, len;
	CrossLinkedList() : len(0), m(0), n(0) {}
};

void CrossLinkedList::createCrossLinkedList(){
	cout << "input the row_size of matrix: ";
	cin >> m;
	cout << "input the col_size of matrix: ";
	cin >> n;
	cout << "input the number of vertices of matrix that val != 0: ";
	cin >> len;
	row_head = vector<Node*>(m);
	col_head = vector<Node*>(n);
	// 输入矩阵的行列数
	for(int i = 0; i < row_head.size(); ++i)
		row_head[i] = new Node(-1, -1, -1);
	for(int j = 0; j < col_head.size(); ++j)
		col_head[j] = new Node(-1, -1, -1);
	int row, col, val;
	for(int i = 0; i < len; ++i){
		cin >> row >> col >> val;
		while(row > row_head.size() || col > col_head.size()){
			cout << "wrong, input again" << endl;
			cin >> row >> col >> val;
		}
		Node * node = new Node(row, col, val);
		Node * p = row_head[row - 1];
		int j = 1;
		// 将该结点插入相应的行表中
		while(j < col && p->right != row_head[row - 1]){
			p = p->right;
			++j;
		}
		node->right = p->right;
		p->right = node;
		Node * q = col_head[col - 1];
		int k = 1;
		while(k < row && q->down != col_head[col - 1]){
			q = q->down;
			++k;
		}
		node->down = q->down;
		q->down = node;
	}
}

void CrossLinkedList::show(){
	for(int i = 0; i < row_head.size(); ++i){
		Node * p = row_head[i];
		while(p->right != row_head[i]){
			cout << p->right->row << " " << p->right->col << " " << p->right->val << endl;
			p = p->right;
		}
	}
	cout << endl;
	for(int i = 0; i < col_head.size(); ++i){
		Node * q = col_head[i];
		while(q->down != col_head[i]){
			cout << q->down->row << " " << q->down->col << " " << q->down->val << endl;
			q = q->down;
		}
	}
}

int main(){
	CrossLinkedList cross_linkedlist;
	cross_linkedlist.createCrossLinkedList();
	cross_linkedlist.show();
	return 0;
}