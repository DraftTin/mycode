#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool Substr(string &s1, string &s2, int k);

int StringMatching(string &s1, string &s2){
	// 外层循环O(n - m), SubStr O(m), 总的复杂度O((n - m) * m)
	if(s1.size() < s2.size())
		return StringMatching(s2, s1);
	for(int i = 0; i <= s1.size() - s2.size(); ++i){
		if(s1[i] == s2[0] && s1[i + s2.size() - 1] == s2[s2.size() - 1]){
			if(Substr(s1, s2, i))
				return i;
		}
	}
	return -1;
}

bool Substr(string &s1, string &s2, int k){
	for(int i = k, j = 0; i < s2.size(); ++i, ++j){
		if(s1[i] != s2[j])
			return false;
	}
	return true;
}


void get_next(vector<int> &next, string &s){
	int i = 0, j = -1;
	next[0] = -1;
	//cout << "next[0] = -1" << endl;
	while(i < s.size() - 1){
		if(j == -1 || s[i] == s[j]){
			++i;
			++j;
			// next[i] = j;
			// 如果这个位置相等回溯时没必要再回溯到相同的字母了
			if(s[i] == s[j]){
				// cout << "s[i] == s[j], ";
				// cout << "i == " << i << ", j == " << j << ", next[" << i+1 << "] <- " << "next[j]:  " << next[j] << endl;
				next[i] = next[j];
			}
			else{
				// cout << "j == -1, ";
				// cout << "i == " << i << ", j == " << j << ", next[" << i+1 << "] <- " << "j:  " << j << endl;
				next[i] = j;
			}
		}
		else{
			// cout << "s[" << i << "]: "  << s[i] << " != s[" << j << "]: "  << s[j] << ", " << "i == " << i << ", j back to " << next[j] << endl;
			j = next[j];
		}
	}
	cout << "next : ";
	for(int i = 0; i < next.size(); ++i)
		cout << next[i] << "  ";
	cout << endl;
}

vector<int> KMP(string &s1, string &s2){
	vector<int> poss;
	if(s1.size() < s2.size())
		return KMP(s2, s1);
	vector<int> next(s2.size());
	get_next(next, s2);
	int i = 0, j = 0;
	int len1 = s1.size(), len2 = s2.size();
	cout << '\n' << "Start matching:" << endl;
	while(i < len1 && j < len2){
		if(j == -1 || s1[i] == s2[j]){
			// if(j != -1)
			// 	cout << "s1[" << i <<"]" << " == s2[" << j << "], ";
			// else
			// 	cout << "j == -1, rematching.."; 
			// cout << "i: " << i << " <- i+1: " << i + 1 << ", j: " << j << " <- j + 1: " << j + 1 << endl; 
			++i;
			++j;
		}
		else{
			// cout << "s1[" << i << "]: "  << s1[i] << " != s2[" << j << "]: "  << s2[j] << ", " << "Character match failed, j: " << j << " <- next[j]: " << next[j] << endl;
			j = next[j];
		}
		if(j == len2){
			poss.push_back(i - j);
			j = -1;
		}
	}
	return poss;
}

int main(){
	string s1;
	string s2;
	cout << "enter the s1: ";
	cin >> s1;
	cout << "enter the s2:";
	cin >> s2;
	vector<int> res = KMP(s1, s2);
	if(res.empty()){
		cout << "not match" << endl;
	}
	for(int i = 0; i < res.size(); ++i)
		cout << res[i] << endl;
	return 0;
}