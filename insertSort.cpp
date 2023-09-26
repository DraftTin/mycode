#include <iostream>
#include <vector>

using namespace std;

class Node{
public:
	int val;
	Node * link;
	Node(int value) : val(value), link(NULL) {}
};

void insertSort(Node*& first){
	Node * head = new Node(0);
	head->link = first;
	Node * p = head->link;
	Node * pre = head;
	while(p){
		Node * tmp = head;
		while(tmp->link != p && tmp->link->val <= p->val){
			tmp = tmp->link;
		}
		if(tmp->link == p){
			pre = p;
			p = p->link;
			continue;
		}
		pre->link = p->link;
		p->link = tmp->link;
		tmp->link = p;
		p = pre->link;
	}
	first = head->link;
}

int main(){
	Node * first = NULL;
	Node * pre = NULL;
	cout << "number:";
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i){
		cout << "val: ";
		int val;
		cin >> val;
		if(first == NULL){
			first = new Node(val);
			pre = first;
			continue;
		}
		Node * current = new Node(val);
		pre->link = current;
		pre = current;
	}
	Node * p = first;
	while(p){
		cout << p->val << " ";
		p = p->link;
	}
	cout << endl;
	insertSort(first);
	p = first;
	while(p){
		cout << p->val << " ";
		p = p->link;
	}
	return 0;
}