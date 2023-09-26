#include <vector>
#include <iostream>

using namespace std;

void swap(int& a, int& b){
	int c = a;
	a = b;
	b = c;
}

void bubbleSort(vector<int>& arr, int begin, int end){
	int bound = end;
	while(bound != begin){
		int t = begin;
		for(int j = begin; j < bound; ++j){
			if(arr[j] > arr[j + 1]){
				swap(arr[j], arr[j + 1]); 
				t = j + 1;
			}
		}
		// t及之后都已经排好序
		bound = t;
		cout << "bound = " << bound << endl;
	}
}

void swapSort(vector<int>& arr){
	int flag = 1;
	while(flag){
		flag = 0;
		for(int i = 1; i < arr.size() - 1; i += 2){
			if(arr[i] > arr[i+1]){
				swap(arr[i], arr[i+1]);
				flag = 1;
			}
		}
		for(int i = 0; i < arr.size() - 1; i += 2){
			if(arr[i] > arr[i+1]){
				swap(arr[i], arr[i+1]);
				flag = 1;
			}
		}
	}
}

void bsort(vector<int>& arr, int begin, int end){
	int bound = end;
	while(bound != begin){
		int t = begin;
		for(int j = begin; j < bound; ++j){
			if(arr[j] > arr[j + 1]){
				swap(arr[j], arr[j + 1]);
				t = j + 1;
			}
		}
		bound = t;
	}
}

int main(){
	vector<int> arr = {5,4,3,2,1};
	bsort(arr, 0, 4);
	for(int item : arr)
		cout << item << endl;
	return 0;
}