#include <iostream>
#include <vector>

using namespace std;

class Node{
public:
	int val;
	Node * next;
	Node(int v) : val(v) {}
};

void  MergeAndReverse(Node *& head1, Node * head2){
	Node * p = head1;
	Node * current = head2->next;
	while(current){
		p = head1;
		while(p->next && p->next->val < current->val) p = p->next;
		Node * tmp = current->next;
		current->next = p->next;
		p->next = current;
		current = tmp;
	}
	Node * p1 = head1;
	Node * p2 = head1->next;
	if(!p2){
		return ;
	}
	Node * p3 = p2->next;
	while(p3){
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
		p2->next = p1;
	}
	head1->next->next = NULL;
	head1->next = p2;
	free(head2);
}

void delete_(Node * head, int i){
	int cnt = 1;
	while(cnt < i && head->next){
		head = head->next;
		++cnt;
	}
	if(!head->next) return ;
	Node * tmp = head->next;
	head->next = tmp->next;
	free(tmp);
}

void insertSort(Node *& head){
	Node * p = head->next;
	while(p->next){
		Node * tmp = head;
		Node * cur = p->next;
		if(cur->val >= p->val){
			p = p->next;
			continue;
		}
		// 这里要 <=, 维持插入排序的稳定性
		while(tmp->next != cur && tmp->next->val <= cur->val) tmp = tmp->next;
		p->next = cur->next;
		cur->next = tmp->next;
		tmp->next = cur;
	}
}

bool judgeArithematicSequence(Node * head){
	// 至少有三个结点
	Node * p = head->next;
	int q = p->next->val - p->val;
	p = p->next;
	while(p->next){
		if(p->next->val - p->val != q) return false;
		p = p->next;
	}
	return true;
}

void printLinkedList(Node * head){
	while(head->next){
		cout << head->next->val << " ";
		head = head->next;
	}
	cout << endl;
}

Node * doNothing(Node * first){
	Node * cur = first;
	if(cur && cur->next){
		Node * q = cur;
		cur = cur->next;
		Node * p = cur;
		while(p->next) p = p->next;
		p->next = q;
		q->next = NULL;
	}
	return cur;   
}

void createLinkedList(Node * head, int n) {
	Node * cur = NULL;
	Node * pre = head;
	for(int i = 0; i < n; ++i){
		cout << "val: ";
		int val;
		cin >> val;
		cur = new Node(val);
		pre->next = cur;
		cur->next = NULL;
		pre = cur;
	}
}

int countX(Node * head, int val){
	Node * p = head;
	int count = 0;
	while(p->next) {
		if(p->next->val == val) ++count;
		p = p->next;
	}
	return count;
}

bool find(Node * head, int val){
	while(head->next){
		if(head->next->val == val) return true;
		head = head->next;
	}
	return false;
}

Node * intersection(Node * head1, Node * head2){
	// 链表取交集，调用函数find查找，注意集合中不能出现重复元素，所以要对head3调用find
	Node * p = head1;
	Node * head3 = new Node(0);
	Node * pre = head3;
	while(p->next){
		if(find(head2, p->next->val) && !find(head3, p->next->val)){
			Node * cur = new Node(p->next->val);
			pre->next = cur;
			cur->next = NULL;
			pre = cur;
		}
		p = p->next;
	}
	return head3;
}

Node * Union(Node * head1, Node * head2){
	// 并集
	Node * head3 = new Node(0);
	Node * pre = head3;
	Node * p = head1;
	while(p->next){
		if(!find(head3, p->next->val)){
			Node * cur = new Node(p->next->val);
			pre->next = cur;
			pre = cur;
			cur->next = NULL;
		}
		p = p->next;
	}
	p = head2;
	while(p->next){
		if(!find(head3, p->next->val)){
			Node * cur = new Node(p->next->val);
			pre->next = cur;
			pre = cur;
			cur->next = NULL;
		}
		p = p->next;
	}	
	return head3;
}

void removeSuperfluousElements(Node * head){
	Node * cur = head->next;
	Node * pre = head;
	while(cur){
		Node * p = head;
		while(p->next != cur && p->next->val != cur->val) p = p->next;
		if(p->next != cur){
			pre->next = cur->next;
			free(cur);
			cur = pre;
		}
		pre = cur;
		cur = cur->next;
	}
}

void selectedSort(Node * head){
	// 链表简单选择排序
	Node * cur = head->next;
	while(cur){
		int minval = cur->val;
		Node * minP = cur;
		Node * p = cur->next;
		while(p){
			if(p->val < minval){
				minP = p;
				minval = p->val;
			}
			p = p->next;
		}
		int tmp = cur->val;
		cur->val = minval;
		minP->val = tmp;
		cur = cur->next;
	}
}

void BubbleSort(Node * head){
	if(!head->next) return ;
	Node * bound = NULL;
	Node * p = head->next;
	while(bound != head->next){
		Node * t = head->next;
		p = head->next;
		while(p->next != bound){
			if(p->next->val < p->val){
				int tmp = p->next->val;
				p->next->val = p->val;
				p->val = tmp;
				t = p->next;
			}
			p = p->next;
		}
		bound = t;
	}
}


int main(){
	Node * head1 = new Node(0);
	Node * head2 = new Node(0);
	createLinkedList(head1, 10);	
	BubbleSort(head1);
	printLinkedList(head1);
	return 0;
}