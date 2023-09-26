#include <iostream>
#include <vector>
#include <stack>
#include <ctime>

using namespace std;

void exchange(int& a, int& b){
	int c = a;
	a = b;
	b = c;
}

int findPartition(vector<int>& arr, int left, int right){
	int mid = (right - left) / 2 + left;
	if(arr[mid] > arr[right]){
		exchange(arr[mid], arr[right]);
	}
	if(arr[left] > arr[right]){
		exchange(arr[left], arr[right]);
	}
	if(arr[mid] > arr[left]){
		exchange(arr[mid], arr[left]);
	}
	return arr[left];
}

void quickSort(vector<int>& arr, int begin, int end){
	// 分割log(n)次, 每次时间复杂度为O(n), 总的时间复杂度为O(nlog(n))
	if(begin >= end)
		return ;
	int i = begin;
	int j = end;
	int lcount = 0;
	int rcount = 0;
	int val = findPartition(arr, begin, end);
	while(i < j){
		while(i < j && arr[j] >= val){
			if(arr[j] == val){
				exchange(arr[j], arr[end - rcount]);
				++rcount;
			}
			--j;
		}
		arr[i] = arr[j];
		while(i < j && arr[i] <= val){
			if(arr[i] == val){
				exchange(arr[i], arr[lcount + begin]);
				++lcount;
			}
			++i;
		}
		arr[j] = arr[i];
	}
	// cout << val << ": " << lcount << " " << rcount << endl;
	arr[i] = val;
	int n = i - 1;
	int m = 0;
	while(m < n && m < lcount){
		exchange(arr[n], arr[m]);
		++m;
		--n;
	}
	n = i + 1;
	m = end;
	while(n < m && end - m < rcount){
		exchange(arr[n], arr[m]);
		--m;
		++n;
	}
	quickSort(arr, begin, i - 1 - lcount);
	quickSort(arr, i + 1 + rcount, end);
}

int Partition(vector<int>& arr, int begin, int end){
	int val = findPartition(arr, begin, end);
	int i = begin, j = end;
	while(i < j){
		while(i < j && arr[j] >= val){
			--j;
		}
		arr[i] = arr[j];
		while(i < j && arr[i] <= val){
			++i;
		}
		arr[j] = arr[i];
	}
	arr[i] = val;
	return i;
}

void quickSortWithoutRecursion(vector<int>& arr, int begin, int end){
	// 非递归快排
	if(begin >= end)
		return ;
	stack<int> sta;
	int bound = Partition(arr, begin, end);
	// 如果还有待排元素，将左右边界两两入栈
	if(begin < bound - 1){
		sta.push(begin);
		sta.push(bound - 1);
	}
	if(end > bound + 1){
		sta.push(bound + 1);
		sta.push(end);
	}
	while(!sta.empty()){
		int right = sta.top();
		sta.pop();
		int left = sta.top();
		sta.pop();
		bound = Partition(arr, left, right);
		// 重复同样的过程，若将左右的区间入栈
		if(left < bound - 1){
			sta.push(left);
			sta.push(bound - 1);
		}
		if(right > bound + 1){
			sta.push(bound + 1);
			sta.push(right);
		}
	}
}


int randomizedPartition(vector<int>& arr, int begin, int end){
	// 随机选择基准元
	srand((int)time(NULL));
	int pos = (rand() % (end - begin + 1)) + begin;
	exchange(arr[pos], arr[begin]);
	int mid = arr[begin];
	int i = begin, j = end;
	while(i < j){
		while(i < j && arr[j] >= mid) --j;
		arr[i] = arr[j];
		while(i < j && arr[i] <= mid) ++i;
		arr[j] = arr[i];
	}
	arr[i] = mid;
	return i;
}

int randomizedSelect(vector<int>& arr, int begin, int end, int i){
	// 寻找第i小的元素，快排思想，只递归一边，期望时间复杂度O(n)，具体推导见算法导论P121
	if(begin == end) return arr[begin];
	int pos = randomizedPartition(arr, begin, end);
	int k = pos - begin + 1; 	// 第k大的元素
	if(k == i) return arr[pos]; // k == i 表示找到了第i小的元素
	else if(k > i) return randomizedSelect(arr, begin, pos - 1, i); // 只递归一边，想二叉搜索树  
	else return randomizedSelect(arr, pos + 1, end, i - k);
}

void quickSortWithRandomizedPartition(vector<int>& arr, int begin, int end){
	if(begin < end){
		int mid = randomizedPartition(arr, begin, end);
		quickSortWithRandomizedPartition(arr, begin, mid - 1);
		quickSortWithRandomizedPartition(arr, mid + 1, end);
	}
	
}

int main(){
	// vector<int> arr = {4,4,4,2,1,5,6,8,4,6};
	vector<int> arr;
	while(true){
		int tmp;
		cin >> tmp;
		if(tmp == -1) break;
		arr.push_back(tmp);
	}
	quickSortWithRandomizedPartition(arr, 0, arr.size() - 1);
	cout << endl; 	
	for(int tmp : arr){
		cout << tmp << " ";
	}
	cout << endl;
	cout << "size = " << arr.size() << endl;
	return 0;
}

// 129 141 155 131 60 83 54 182 102 152 104 137 116 41 148 86 71 14 48 113 172 146 52 39 158 95 118 50 22 61 34 12 47 153 35 159 136 121 1 178 167 198 8 24 3 56 133 127 170 11 

// 54 56 60 61 71 83 86 95 102 104 113 116 118 121 127 129 131 133 136 137 141 146 148 152 153 155 158 159 167 170 172 178 182 198 52 50 48 47 41 39 35 34 24 22 14 12 11 8 3 1 
