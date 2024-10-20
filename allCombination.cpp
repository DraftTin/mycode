#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void addOne(vector<int>& comb){
	if(comb.empty()) return ;
	comb[0] += 1;
	int i = 0;
	while(comb[i] == 2){
		comb[i] = 0;
		++i;
		if(i == comb.size()) break;
		comb[i] += 1;
	}
}

void allCombination(int n) {
	vector<int> comb(n, 0);
	int t = pow(2, n);
	cout << "##:  null" << endl;
	for(int i = 0; i < t - 1; ++i) {
		addOne(comb);
		cout << "##:  ";
		for(int j = 0; j < comb.size(); ++j) {
			if(comb[j] == 1) cout << j << " ";
		}
		cout << endl;
	}
}

int main(){
	int n;
	cin >> n;
	allCombination(n);
	return 0;
}
