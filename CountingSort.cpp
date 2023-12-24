#include <iostream>
#include <vector>

using namespace std;

void countingSort(vector<int>& arr, int begin, int end){
	// 时间复杂度: O(max{arr} - min{arr} + n)
	// 稳定
	if(begin >= end)
		return ;
	int max = INT_MIN, min = INT_MAX;
	int offset = 0;
	for(int i = begin; i <= end; ++i){
		if(arr[i] < 0 && min > arr[i]){
			min = arr[i];
			offset = -arr[i];
		}
		if(arr[i] > max){
			max = arr[i];
		}
	}
	max = max > 0 ? max : 1;
	vector<int> new_arr(end - begin + 1);
	vector<int> counting(offset + max + 1, 0);
	for(int i = begin; i <= end; ++i){
		++counting[arr[i] + offset];
	}
	for(int i = 1; i < counting.size(); ++i){
		counting[i] = counting[i] + counting[i - 1];
	}
	// 这里需要从尾到头才能保证排序是稳定的
	for(int i = end; i >= begin; --i){
		--counting[arr[i] + offset];
		new_arr[counting[arr[i] + offset]] = arr[i];		
	}
	for(int i = begin; i <= end; ++i){
		arr[i] = new_arr[i - begin];
	}
}

void normalCountingSort(vector<int>& arr, int k){
	// 此处k可以看成进制数，如十进制开大小为10的数组count，用于基数排序
	// 时间复杂度上界 O(n + k)
	// 将每个位置的值都初始化为0
	vector<int> count(k, 0);
	vector<int> new_arr(arr.size());
	for(int i = 0; i < arr.size(); ++i){ 
		++count[arr[i]];
	}
	// count[i] contains the number of elements less than or equals to i
	for(int i = 1; i < count.size(); ++i){ 
		count[i] += count[i - 1];
	}
	for(int i = arr.size() - 1; i >= 0; --i){
		// 对应位置赋值
		--count[arr[i]];
		new_arr[count[arr[i]]] = arr[i];
	}
	arr = new_arr;
}

int main(void){
	vector<int> arr({5,4,2,0,6,3,0});
	normalCountingSort(arr, 7);
	for(int tmp : arr){
		cout << tmp << " ";
	}
	cout << endl;
	return 0;
}