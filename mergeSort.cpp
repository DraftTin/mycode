#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void merge1(vector<int>& arr, int begin, int mid, int end){
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

void mergeSort1(vector<int>& arr, int begin, int end){
	// 分割log(n)次, 每次O(2n), 总的时间复杂度O(2*n*log(n)) ---> O(n*log(n))
	// 空间复杂度O(n)
	if(begin < end){
		int mid = (begin + end) / 2;
		mergeSort1(arr, begin, mid);
		mergeSort1(arr, mid + 1, end);
		merge1(arr, begin, mid, end);
	}
}

int insertSort_(vector<int>& arr, vector<int>& link, int begin, int end){
	for(int i = begin + 1; i < end + 1; ++i){
		link[i] = i + 1;
	}
	link[end + 1] = 0;
	link[0] = begin + 1;
	int i = link[0];
	int pre = 0;
	while(i != 0){
		int tmp = 0;
		while(link[tmp] != i && arr[link[tmp] - 1] <= arr[i - 1]){
			tmp = link[tmp];
		}
		if(link[tmp] == i){
			pre = i;
			i = link[i];
			continue;
		}
		link[pre] = link[i];
		link[i] = link[tmp];
		link[tmp] = i;
		i = link[pre];
	}
	// cout << "begin: " << begin << endl;
	// for(int tmp : arr) cout << tmp << " ";
	// cout << endl;
	// int n = link[0];
	// while(n != 0){
	// 	cout << n << " ";
	// 	n = link[n];
	// }
	// cout << 0 << endl;
	// cout << "end: " << end << endl;
	return link[0];
}

// 返回计算出的表头位置
int merge2(vector<int>& arr, vector<int>& link, int q, int r){
	 // 从两个表的表头开始 i, j
	 // 构建新的表, link[0] 表示新的表的表头 link[1]表示arr数组中arr[0]在表中下一个元素
	 int i = q;
	 int j = r;
	 int k = 0;
	 while(i != 0 && j != 0){
	 	if(arr[i - 1] < arr[j - 1]){
	 		link[k] = i;
	 		k = i;
	 		i = link[i];
	 	}
	 	else{
	 		link[k] = j;
	 		k = j;
	 		j = link[j];
	 	}
	 }
	 if(i == 0) link[k] = j;
	 else link[k] = i;
	 return link[0];
}

int ms(vector<int>& arr, vector<int>& link, int begin, int end){
	if(end - begin + 1 < 10){
		return insertSort_(arr, link, begin, end);
	}
	else {
		// 返回表的起始元素, 即在arr中的位置,从1开始
		int mid = (begin + end) / 2;
		int q = ms(arr, link, begin, mid);
		int r = ms(arr, link, mid + 1, end);
		return merge2(arr, link, q, r);
	}
}



vector<int> mergeSort2(vector<int>& arr, int begin, int end){
	vector<int> link(arr.size() + 1, 0); // link[i]表示arr数组中arr[i - 1]中指向的下一个位置
	ms(arr, link, begin, end);

	int i = link[0];
	while(i != 0){
		cout << arr[i - 1] << " ";
		i = link[i];
	}
	cout << endl;
	return link;
}
//////////////////////////////////////////


void mergeLen(vector<int>& arr, int begin, int last, int length){
	int i;
	for(i = begin; i + 2 * length - 1 <= last; i += 2 * length){
		merge1(arr, i, i + length - 1, i + 2 * length - 1);
	}
	if(i + length <= last){
		merge1(arr, i, i + length - 1, last);
	}
}

void mergeSort3(vector<int>& arr, int begin, int last){
	int n = last -  begin + 1;
	cout << "unordered: ";
	for(int tmp : arr){
		cout << tmp << " ";
	}
	cout << endl;
	int i = 1;
	for(int length = 1; length < n; length *= 2){
		mergeLen(arr, begin, last, length);
	}
}



int main(){
	srand(int(time(0)));
	int n = 5;
	vector<int> arr(n);
	for(int i = 0; i < arr.size(); ++i){
		cin >> arr[i];
	}

	mergeSort2(arr, 0, arr.size() - 1);
	cout << "ordered: " << endl;
	for(int tmp : arr){
		cout << tmp << " ";
	}
	cout << endl;
	// for(int n = 1000; n <= 100000000; n *= 10){
	// 	vector<int> arr(n);
	// 	for(int i = 0; i < arr.size(); ++i){
	// 		arr[i] = rand() % (2 * n);
	// 	}
	// 	vector<int> arr_copy = arr;
	// 	clock_t start = clock();
	// 	mergeSort2(arr, 0, arr.size() - 1);
	// 	clock_t end = clock();
	// 	cout << "size: " << n << "---" << endl;
	// 	cout << "The improved version mergeSort cost: " << (double(end - start) * 1000 / CLOCKS_PER_SEC) << " ms" << endl;
	// 	start = clock();
	// 	mergeSort1(arr, 0, arr.size());
	// 	end = clock();
	// 	cout << "The normal version mergeSort cost: " << (double(end - start) * 1000 / CLOCKS_PER_SEC) << " ms" << endl;
	// }
	return 0;
}