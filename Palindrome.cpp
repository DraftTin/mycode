#include <iostream>
#include <vector>
#include <string>

using namespace std;

int lcs(string& str1, string& str2){
	int m = str1.size();
	int n = str2.size();
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
	// O(m * n)
	for(int i = 1; i < m + 1; ++i){
		for(int j = 1; j < n + 1; ++j){
			if(str1[i - 1] == str2[j - 1]){
				dp[i][j] = 1 + dp[i - 1][j - 1];
			}
			else{
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	return dp[m][n];
}

void solution(string& s){
	string s_reverse(s);
	for(int i = 0, j = s_reverse.size() - 1; i < j; ++i, --j){
		char c = s_reverse[i];
		s_reverse[i] = s_reverse[j];
		s_reverse[j] = c;
	}
	cout << s.size() - lcs(s, s_reverse) << endl;
	for(int i = 0; i < s.size(); ++i){
		if(s[i] != s_reverse[i]){
			cout << s[i] << s_reverse[i];
		}
		else{
			cout << s[i];
		}
	}
	cout << endl;
}
	
int main(){
	string s;
	cin >> s;
	solution(s);
	return 0;
}