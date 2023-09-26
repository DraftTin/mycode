#include <iostream>
#include <queue>
#include <ctime>

using namespace std;

class Node{
public:
	int val;
	Node * left;
	Node * right;
	Node() : left(NULL), right(NULL) {}
	Node(int val) : val(val), left(NULL), right(NULL) {}
};

class BTree{
public:
	void createBT();
	void inOrder(Node * node);
	void preOrder(Node * node);
	Node * root;
};

void BTree::createBT(){
	int val;
	cin >> val;
	if(val == 0) return ;
	root = new Node();
	root->val = val;
	queue<Node*> que;
	que.push(root);
	while(!que.empty()){
		Node * tmp = que.front();
		que.pop();
		cin >> val;
		if(val != 0){
			tmp->left = new Node(val);
			que.push(tmp->left);
		}
		cin >> val;
		if(val != 0){
			tmp->right = new Node(val);
			que.push(tmp->right);
		}
	}
}

void BTree::inOrder(Node * node){
	if(node != NULL){
		inOrder(node->left);
		cout << node->val << endl;
		inOrder(node->right);
	}
}

void BTree::preOrder(Node * node){
	if(node != NULL){
		cout << node->val << endl;
		preOrder(node->left);
		preOrder(node->right);
	}
}

int isSimilar(Node * node1, Node * node2){
	if(node1 && node2) return (isSimilar(node1->left, node2->left) && isSimilar(node1->right, node2->right)) 
								|| (isSimilar(node1->left, node1->right) && isSimilar(node1->right, node2->left));
	else if (node1 || node2) return false;
	else return true;
}

void qsort(vector<int>& arr, int begin, int end){
	if(begin >= end) return;
	int mid = arr[begin];
	int l = begin;
	int r = end;
	while(l < r){
		while(l < r && arr[r] >= mid) --r;
		arr[l] = arr[r];
		while(l < r && arr[l] <= mid) ++l;
		arr[r] = arr[l];
	}
	arr[l] = mid;
	qsort(arr, begin, l - 1);
	qsort(arr, l + 1, end);
}

void merge(vector<int>& arr, int begin, int mid, int end){
	int n1 = mid - begin + 1;
	int n2 = end - mid;
	vector<int> arr1(n1 + 1);
	vector<int> arr2(n2 + 1);
	for(int i = 0; i < n1; ++i){
		arr1[i] = arr[begin + i];
	}
	for(int j = 0; j < n2; ++j){
		arr2[j] = arr[mid + j + 1];
	}
	arr1[arr1.size() - 1] = INT_MAX;
	arr2[arr2.size() - 1] = INT_MAX;
	int i = 0, j = 0;
	for(int k = begin; k <= end; ++k){
		if(arr1[i] > arr2[j]){
			arr[k] = arr2[j];
			++j;
		}
		else{
			arr[k] = arr1[i];
			++i;
		}
	}
}

void mergeSort(vector<int>& arr, int begin, int end){
	if(begin < end){
		int mid = (begin + end) / 2;
		mergeSort(arr, begin, mid);
		mergeSort(arr, mid + 1, end);
		merge(arr, begin, mid, end);
	}
}

int main(){
	int n;
	cin >> n;
	vector<int> arr(n, 0);
	srand(time(0));
	for(int& tmp : arr) tmp = rand() % (2 * n);

	mergeSort(arr, 0, arr.size() - 1);
	for(int& tmp : arr) cout << tmp << " ";
	cout << endl;
	return 0;
}