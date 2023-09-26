#include <iostream>
#include <vector>

using namespace std;

vector<int> PrimeNumber(int n){
	vector<bool> is_prime(n + 1, true);
	vector<int> prime_number;
	int count = 0;
	for(int i = 2; i < is_prime.size(); ++i){
		if(is_prime[i]){
			++count;
			prime_number.push_back(i);
			for(int j = i; j * i <= n; ++j){
				is_prime[i * j] = false;
			}
		}
	}
	cout << "count = " << count << endl;
	return prime_number;
}

int main(){
	vector<int> prime_number = PrimeNumber(100);
	for(int i = 1; i < prime_number.size(); ++i){
		cout << prime_number[i] << endl;
	}
	return 0;
}