#include <iostream>
#include <vector>

using namespace std;


void shellSort(vector<int>& arr, int begin, int end){
	for(int gap = (end - begin + 1) / 2; gap > 0; gap /= 2){
		for(int i = begin; i <= end - gap; ++i){
			int tmp = arr[i + gap];
			int k = i;
			while(k >= begin && arr[k] > tmp){
				arr[k + gap] = arr[k];
				k -= gap;
			}
			arr[k + gap] = tmp;
		}
	}
}

void insertSort(vector<int>& arr, int begin, int end){
	for(int i = begin; i <= end - 1; ++i){
		int tmp = arr[i + 1];
		int k = i;
		while(k >= begin && arr[k] > tmp){
			arr[k + 1] = arr[k];
			--k;
		}
		// arr[k] <= arr[i + 1]
		arr[k + 1] = tmp;
	}
}

int main(){
	vector<int> arr(10, 0);
	cout << endl;
	return 0;
}