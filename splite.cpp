#include <iostream>
#include <vector>

using namespace std;

void solution(int curNum, vector<int>& curCombination, int pos, vector<vector<int>>& res){
	if(curNum == 0 && pos >= 2){
		res.push_back(curCombination);
		return ;
	}
	for(int i = 1; i <= curNum; ++i){
		if(pos > 0 && i < curCombination[pos - 1]) continue;
		curCombination[pos] = i;
		solution(curNum - i, curCombination, pos + 1, res);
	}
}

vector<vector<int>> splite(int num){
	vector<vector<int>> res;
	vector<int> curCombination(num);
	solution(num, curCombination, 0, res);
	return res;
}

void show(){
	int num;
	cin >> num;
	if(num < 2) return ;
    vector<vector<int>> res = splite(num);
    cout << "size = " << res.size() << endl;
    for(vector<int> tmp : res){
    	int n = num;
    	for(int i : tmp){
    		cout << i << " ";
    		n -= i;
    		if(n == 0) break;
    	}
    	cout << endl;
    }
}

int main(){
	show();
    return 0;
}