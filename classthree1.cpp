#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

int compareCounting = 0;
float averge_compareCounting = 0;

int LEFT(int i){
	return 2 * i + 1;
}

int RIGHT(int i){
	return 2 * i + 2;
}

void exchange(int& a, int& b){
	int c = a;
	a = b;
	b = c;
}

void heap_maxify(vector<int>& arr, int pos, int heapsize){
	int largest = pos;
	int left = LEFT(pos);
	int right = RIGHT(pos);
	if(left < heapsize && arr[left] > arr[pos]){
		++compareCounting;
		largest = left;
	}
	if(right < heapsize && arr[right] > arr[largest]){
		++compareCounting;
		largest = right;
	}
	if(largest != pos){
		exchange(arr[pos], arr[largest]);
		heap_maxify(arr, largest, heapsize);
	}
}

void Build_Max_Heap(vector<int>& A){
	for(int i = A.size() / 2 - 1; i >= 0; --i){
		heap_maxify(A, i, A.size());
	}
}

void heap_sort(vector<int>& A){
	Build_Max_Heap(A);
	int heapsize = A.size();
	for(int i = 0; i < A.size() - 1; ++i){
		exchange(A[0], A[heapsize-1]);
		--heapsize;
		heap_maxify(A, 0, heapsize);
	}
}

void swap(int& a, int& b){
	int c = a;
	a = b;
	b = c;
}

void insert_(vector<int>& A, int val){
	A.push_back(val);
	for(int i = A.size() - 1; i > 0; i = (i - 1) / 2){
		if(A[(i - 1) / 2] < A[i])
			swap(A[(i - 1) / 2], A[i]);
		else
			break;
	}
}

void delete_(vector<int>& A, int pos){
	A[pos] = A[A.size() - 1];
	A.pop_back();
	for(int i = pos; 2 * i + 1 < A.size(); ){
		int largest = i;
		if(A[i] < A[2 * i + 1]){
			largest = 2 * i + 1;
		}
		if(2 * i + 2 < A.size() && A[largest] < A[2 * i + 2]){
			largest = 2 * i + 2;
		}
		if(largest == i)
			break;
		swap(A[largest], A[i]);
		i = largest;
	}
}

int main(){
	vector<int> arr = {1,2,3,4,5};
	Build_Max_Heap(arr);
	for(int i : arr){
		cout << i << " ";
	}
	cout << endl;
	insert_(arr, 6);	
	for(int i : arr){
		cout << i << " ";
	}
	cout << endl;
	delete_(arr, 0);
	for(int i : arr){
		cout << i << " ";
	}
	cout << endl;
	return 0;
}

// int main(){
// 	ofstream out( "classthree1text.txt", ios::trunc | ios::out);
// 	out.close();
// 	srand(time(NULL));	
// 	for(int i = 0; i < 10; ++i){
// 		ofstream fout( "classthree1text.txt", ios::app | ios::out); 
// 	    streambuf * OldBuf = cout.rdbuf( fout.rdbuf( ) );
	    
// 		vector<int> arr(10);
		
// 		for(int i = 0; i < arr.size(); ++i){
// 			arr[i] = (int)((rand() + 10) % 1000001);
// 			cout << arr[i] << " ";
// 		}
// 		cout << endl;
// 		heap_sort(arr);
// 		averge_compareCounting += compareCounting;
// 		for(int item : arr){
// 			cout << item << " ";	
// 		}
// 		cout << endl << compareCounting << endl;
// 		compareCounting = 0;
// 		cout.rdbuf( OldBuf );
// 		fout.close();
// 	}
// 	ofstream fout( "classthree1text.txt", ios::app | ios::out);
// 	streambuf * OldBuf = cout.rdbuf( fout.rdbuf( ) );
// 	cout << averge_compareCounting / 10 << endl;
// 	fout.close();
//     return 0;
// }