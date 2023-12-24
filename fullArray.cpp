#include <iostream>
#include <vector>

using namespace std;

void fullArray(vector<int>& arr, vector<int>& seq, int pos, vector<int>& visited, vector<vector<int>>& res){
	if(pos == arr.size()){
		res.push_back(seq);
		return ;
	}
	for(int i = 0; i < arr.size(); ++i){
		if(!visited[i]){
			visited[i] = 1;
			seq[pos] = arr[i];
			fullArray(arr, seq, pos + 1, visited, res);
			visited[i] = 0;
		}
	}
}


void fullArray1(int n){
	if(n <= 0) return ;
	vector<int> arr(n);
	vector<int> seq(n);
	vector<int> visited(n, 0);
	vector<vector<int>> res;
	for(int i = 0; i < n; ++i){
		arr[i] = i;
	}
	for(int i = 0; i < arr.size(); ++i){
		if(!visited[i]){
			visited[i] = 1;
			seq[0] = arr[i];
			fullArray(arr, seq, 1, visited, res);
			visited[i] = 0;
		}
	}
	cout << "size = " << res.size() << endl;
	for(vector<int> tmp : res){
		for(int i : tmp){
			cout << i << " ";
		}
		cout << endl;
	}
}

void exchange(int& a, int& b){
	int c = a;
	a = b;
	b = c;
}

void fullArray2(int n){
	// -1表示方向左 1表示方向右 
	vector<int> dir(n, -1);
	vector<int> arr(n);
	for(int i = 0; i < n; ++i) arr[i] = i;
	for(int tmp : arr) cout << tmp << " ";
	cout << endl;
	while(true){
		int maxIndex = -1;
		int maxVal = INT_MIN;
		for(int i = 0; i < n; ++i){
			int pos = i + dir[i];
			if(pos >= 0 && pos < n && arr[pos] < arr[i] && arr[i] > maxVal){
				maxIndex = i;
				maxVal = arr[i];
			}
		}
		if(maxIndex == -1) break;
		exchange(arr[maxIndex], arr[maxIndex + dir[maxIndex]]);
		exchange(dir[maxIndex], dir[maxIndex + dir[maxIndex]]);
		for(int i = 0; i < n; ++i){
			if(arr[i] > maxVal) dir[i] = -dir[i];
		}
		for(int tmp : arr){
			cout << tmp << " ";
		}
		cout << endl;
	}
}

int main(){
	int n;
	cin >> n;
	fullArray2(n);
	return 0;
}