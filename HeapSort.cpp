// 复习堆排序算法和优先队列和HuffmanTree算法
#include <iostream>
#include <vector>

using namespace std;

int LEFT(int i){
	return 2 * i + 1;
}

int RIGHT(int i){
	return 2 * i + 2;
}

int PARENT(int i){
	return (i-1) / 2;
}

void exchange(int& a, int& b){
	int c = a;
	a = b;
	b = c;
}

void Heap_maxify(vector<int>& arr, int i, int heapsize){
	int l = LEFT(i);
	int r = RIGHT(i); //l, r分别代表结点的左侧和右侧在数组中的位置
	int largest = i;
	if(l < heapsize && arr[l] > arr[i])
		largest = l;
	if(r < heapsize && arr[r] > arr[largest])
		largest = r;
	if(largest != i){
		exchange(arr[i], arr[largest]);
		Heap_maxify(arr, largest, heapsize);
	}
}

void Build_Max_Heap(vector<int>& A){
	for(int i = A.size() / 2 - 1; i >= 0; --i){
		Heap_maxify(A, i, A.size());
	}
}

void Heap_sort(vector<int>& A){
	Build_Max_Heap(A);
	int heapsize = A.size();
	for(int i = 0; i < A.size() - 1; ++i){
		exchange(A[0], A[heapsize-1]);
		--heapsize;
		Heap_maxify(A, 0, heapsize);
	}
}
//以上为堆排序, 时间复杂度:第一行n*log(n), 循环n*log(n), 总体上O(n*log(n))
int Heap_Maximum(vector<int>& A){
	return A[0];
}

void Heap_increase_key(vector<int>& A, int i, int key){
	if(key < A[i]){
		cout << "The key is smaller than the current key" << endl;
		return ;
	}
	A[i] = key;
	while(i > 0 && A[i] > A[PARENT(i)]){
		exchange(A[i], A[PARENT(i)]);
		i = PARENT(i);
		cout << "i = " << i << endl;
	}
}

void maxInsert(vector<int>& A, int key){
	A.push_back(INT_MIN);
	cout << A.size() - 1 << endl;
	Heap_increase_key(A, A.size() - 1, key);
}

int Extract_Max(vector<int>& A){
	int tmp = A.front();
	// TODO 这里应该采用和最后元素交换之后下沉的操作
	A.erase(A.begin());
	return tmp;
}

//以上是最大优先队列

void Heap_Minify(vector<int>& A, int i, int heapsize){
	int l = LEFT(i);
	int r = RIGHT(i);
	int min = i;
	if(l < heapsize && A[l] < A[i])
		min = l;
	if(r < heapsize && A[r] < A[min])
		min = r;
	if(min != i){
		exchange(A[i], A[min]);
		Heap_Minify(A, min, heapsize);
	}
}

void Heap_decrease_key(vector<int>& A, int i, int key){
	if(key > A[i]){
		cout << "The key is bigger than the current key" << endl;
		return ;
	}
	A[i] = key;
	while(i > 0 && A[i] < A[PARENT(i)]){
		exchange(A[i], A[PARENT(i)]);
		i = PARENT(i);
	}
}

void minInsert(vector<int>& A, int key){
	A.push_back(INT_MAX);
	Heap_decrease_key(A, A.size() - 1, key);
}

int Extract_Min(vector<int>& A){
	int tmp = A.front();
	A.erase(A.begin());
	return tmp;
}

int Huffman(vector<int>& C){
	int n = C.size();
	vector<int> Q = C;
	for(int i = 0; i < n-1; ++i){
		int a = Extract_Min(Q);
		int b = Extract_Min(Q);
		int sum = a + b;
		cout << "a = " << a << endl;
		cout << "b = " << b << endl;
		minInsert(Q, sum);
	}
	return Extract_Min(Q);
}



int main(void){
	vector<int> arr({5,4,3,2,1});
	Heap_sort(arr);
	for(int tmp : arr)
		cout << tmp << endl;
	return 0;
} 