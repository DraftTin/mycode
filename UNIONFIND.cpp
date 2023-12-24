#include <iostream>
#include <vector>

using namespace std;

class Node{
public:
	int rank;	//秩
	Node * p;
	int val;
	Node() : rank(0), p(this), val(0) {}
};
 
Node * FindSet(Node *item)
{
	if(item->p != item)
		item->p = FindSet(item->p);
	return item->p;
}

void Union(Node * lhs, Node * rhs){ 
	Node * lhsroot, * rhsroot;
	lhsroot = FindSet(lhs);
	rhsroot = FindSet(rhs);
	if(rhsroot->rank > lhsroot->rank){
		lhsroot->p = rhsroot;
	}
	else{
		rhsroot->p = lhsroot;
		if(lhsroot->rank == rhsroot->rank)
			lhsroot->rank++;
	}
}

Node * MakeSet(){
	Node * node = new Node;
	cout << "please input the value : ";
	int value;
	cin >> value;
	node->val = value;
	return node;
}

int main(void){
	vector<Node*> items;
	for(int i = 0; i < 5; ++i)
		items.push_back(MakeSet());
	Union(items[0], items[2]);
	Union(items[1], items[3]);
	Union(items[0], items[3]);
	FindSet(items[3]);
	for(int i = 0; i < 5; ++i)
		cout << items[i]->p->val << endl;
	for(int i = 0; i < 5; ++i)
		delete items[i];
	return 0;
}