#include <iostream>
#include <vector>

using namespace std;

class Node{
public:
	Node * next;
	int val;
	Node(int v) : next(NULL), val(v) {}
};

class Node_ {
public:
	Node_ * prev;
	Node_ * next;
	int val;
	Node_(int v) : next(NULL), prev(NULL), val(v) {}
};

class LinkedList{
public:
	Node * head;
	LinkedList() : head(new Node(0)), length(0) {}
	void createLinkList(); 		//创建链表
	void createLinkListAsc();	//创建非降序链表
	void printLinkList_sum();	//输出链表值的和
	void printLinkList_max();	//输出最大最小值
	void printLinkList();		//输出链表
	int Size() {return length;}//长度
private:
	int length;
};


class DoubleSidesCircularLinkedList{
public:
	Node_ * node;
	DoubleSidesCircularLinkedList() : node(NULL) {}
	DoubleSidesCircularLinkedList(LinkedList * linkedlist); 						//用单链表创建双向链表
	void creatDoubleSidesCircularLinkedList();										//创建双向链表
	void creatDoubleSidesCircularLinkedListByLinkedList(LinkedList * linkedlist);	//创建双向链表根据单链表
	void printLinkList(Node_ * start);												//根据结点输出双向链表
	Node_ * findNode();																//查找结点
private:
	Node_ * findNode(int val, int pos);
};

Node_ * DoubleSidesCircularLinkedList::findNode(){
	int val;
	cout << "enter the value you want to find: ";
	cin >> val;
	int pos;
	cout << "start position:";
	cin >> pos;
	return findNode(val, pos);
}

Node_ * DoubleSidesCircularLinkedList::findNode(int val, int pos){
	if(node == NULL){
		return NULL;
	}
	Node_ * current = node;
	int pp = 1;
	if(current->val == val && pp >= pos)
		return current;
	++pp;
	current = current->next;
	while(current != node){
		if(current->val == val && pp >= pos)
			return current;
		current = current->next;
		++pp;
	}
	return NULL;
}

void DoubleSidesCircularLinkedList::creatDoubleSidesCircularLinkedListByLinkedList(LinkedList * linkedlist){
	if(node != NULL){
		cout << "the linkedlist has been modified " << endl;
		return ;
	}
	Node * p = linkedlist->head->next;
	Node_ * current = NULL;
	Node_ * prev = NULL;
	while(p != NULL){
		current = new Node_(p->val);
		if(node == NULL){
			node = current;
			prev = current;
			current->next = node;
			node->prev = node;
		}
		else{
			current->next = node;
			current->prev = prev;
			prev->next = current;
			prev = current;
			node->prev = current;
		}
		p = p->next;
	}
}

DoubleSidesCircularLinkedList::DoubleSidesCircularLinkedList(LinkedList * linkedlist){
	Node * p = linkedlist->head->next;
	Node_ * current = NULL;
	Node_ * prev = NULL;
	while(p != NULL){
		current = new Node_(p->val);
		if(node == NULL){
			node = current;
			prev = current;
			node->prev = node;
		}
		else{
			current->next = node;
			current->prev = prev;
			prev->next = current;
			prev = current;
			node->prev = current;
		}
		p = p->next;
	}
}

void DoubleSidesCircularLinkedList::printLinkList(Node_ * start){
	Node_ * current = start;
	if(current == NULL){
		cout << "not found" << endl;
		return ;
	}
	cout << "[" << current->val << "]" << "->";
	current = current->next;
	while(current != start){
		cout << "[" << current->val << "]" << "->";
		current = current->next;
	}
	cout << "start" << endl;
	cout << endl;
}

void DoubleSidesCircularLinkedList::creatDoubleSidesCircularLinkedList(){
	if(node != NULL){
		cout << "existed" << endl;
		return ;
	}
	Node_ * prev = NULL;
	Node_ * current = NULL;
	while(true){
		int value;
		cout << "enter the value: ";
		cin >> value;
		current = new Node_(value);
		if(node == NULL){
			node = current;
			prev = current;
			current->next = node;
			node->prev = node;
		}
		else{
			current->next = node;
			current->prev = prev;
			prev->next = current;
			prev = current;
			node->prev = current;
		}
		cout << "exit: 0, continue: 1" << endl;
		int tmp;
		cin >> tmp;
		if(tmp == 0)
			break;
	}
	// current = node;
	// cout << current->val << endl;
	// current = current->prev;
	// while(current != node){
	// 	cout << current->val << endl;
	// 	current = current->prev;
	// }
}

void LinkedList::printLinkList(){
	Node * tmp = head;
	while(tmp->next){
		cout << "[" << tmp->next->val << "]" << "->";
		tmp = tmp->next;
	}
	cout << "NULL" << endl;
}

void LinkedList::printLinkList_sum(){
	Node * tmp = head;
	int sum = 0;
	while(tmp->next){
		cout << "[" << tmp->next->val << "]" << "->";
		sum += tmp->next->val;
		tmp = tmp->next;
	}
	cout << "NULL" << endl;
	cout << "length = " << Size() << endl;
	cout << "sum = " << sum << endl;
}



void LinkedList::printLinkList_max(){
	Node * tmp = head;
	int max = INT_MIN;
	int min = INT_MAX;
	vector<int> nums;
	while(tmp->next){
		nums.push_back(tmp->next->val);
		max = tmp->next->val > max ? tmp->next->val : max;
		min = tmp->next->val < min ? tmp->next->val : min;
		tmp = tmp->next;
	}
	for(int i = nums.size() - 1; i >= 0; --i){
		cout << "[" << nums[i] << "]" << "<-";
	}
	cout << "head" << endl;
	cout << "max = " << max << endl;
	cout << "min = " << min << endl;
}

void LinkedList::createLinkList(){
	if(head->next != NULL){
		cout << "LinkList has been modified." << endl;
		return ;
	}
	int num;
	Node * current = NULL;
	Node * prev = head;
	while(true){
		cout << "enter the value:";
		cin >> num;
		current = new Node(num);
		prev->next = current;
		prev = current;
		++length;
		cout << "exit: 0, continue: 1" << endl;
		int tmp;
		cin >> tmp;
		if(tmp == 0)
			break;
	}
	// current = head->next;
	// while(current){
	// 	cout << current->val << endl;
	// 	current = current->next;
	// }
}

void LinkedList::createLinkListAsc(){
	if(head->next != NULL){
		cout << "LinkList has been modified." << endl;
		return ;
	}
	int num;
	Node * current = NULL;
	Node * p = head;
	while(true){
		cout << "enter the value:";
		cin >> num;
		current = new Node(num);
		p = head;
		while(p->next && p->next->val < current->val){
			p = p->next;
		}
		current->next = p->next;
		p->next = current;
		++length;
		cout << "exit: 0, continue: 1" << endl;
		int tmp;
		cin >> tmp;
		if(tmp == 0)
			break;
	}
	// current = head->next;
	// while(current){
	// 	cout << current->val << endl;
	// 	current = current->next;
	// }
}

int main(){
	cout << "Asc LinkedList(L2): " << endl;
	LinkedList * L2 = new LinkedList();
	L2->createLinkListAsc();
	// L2->printLinkList();
	L2->printLinkList_sum();
	cout << "LinkedList(L1): " << endl;
	LinkedList * linkedlist = new LinkedList();
	linkedlist->createLinkList();
	cout << endl;
	linkedlist->printLinkList_max();
	//cout << endl;
	//linkedlist->printLinkList_sum();
	cout << "DoubleSidesCircularLinkedList(L3): " << endl;
	DoubleSidesCircularLinkedList * dscll = new DoubleSidesCircularLinkedList();
	dscll->creatDoubleSidesCircularLinkedListByLinkedList(linkedlist); 
	dscll->printLinkList(dscll->findNode());
	return 0;
}