#include <iostream>
#include <vector>

using namespace std;

void solution(int target, vector<int>& articles, int n, vector<int>& cur, int pos, vector<vector<int>>& res){
	if((n == 0 && target != 0) || target < 0) return ;
	if(target == 0){
		res.push_back(vector<int>(cur.begin(), cur.begin() + pos));
		return;
	}
	cur[pos] = articles[n - 1];
	solution(target - articles[n - 1], articles, n - 1, cur, pos + 1, res);
	solution(target, articles, n - 1, cur, pos, res);
}

bool judge(int target, vector<int>& articles, int n){
	if(target - articles[n - 1] == 0) return true;
	if(target - articles[n - 1] > 0){
		if(judge(target - articles[n - 1], articles, n - 1)) return true;
		else return judge(target, articles, n - 1);
	}
	else{
		if(n > 0) return judge(target, articles, n - 1);
		else return false;
	}
}

int main(){
	vector<int> articles = {2,2,4,2,6};
	vector<int> cur(5);
	vector<vector<int>> res;
	// if(judge(7, articles, articles.size())) cout << "ok" << endl;
	// else cout << "no" << endl;
	solution(7, articles, articles.size(), cur, 0, res);
	for(vector<int>& tmp : res){
		for(int i : tmp){
			cout << i << " ";
		}
		cout << endl;
	}
	return 0;
}