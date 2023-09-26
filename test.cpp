// #include <iostream>

// using namespace std;

// int n, L, A, B;   
// int temp;
// int V;

// int main(){
//     cin >> n >> L >> A >> B;
//     for(int i = 0; i < n; ++i){
//         int opt, x;
//         cin >> opt;
//         if(opt == 1){
//             cin >> x;
//             if(V != 0) temp = x; 
//         }
//         else if(opt == 2){
//             cin >> x;
//             V = x;
//         }
//         else{
//             if(V > L && temp >= A && temp <= B){
//                 cout << temp << endl;
//             }
//             else cout << "GG" << endl;
//         }
//     }
//     return 0;
// }

#include <iostream>
#include <vector>

using namespace std;

int r1[100000], r2[100000];
int cnt;

int main(){
	vector<int> card1;
	vector<int> card2;
	
	int n;
	cin >> n;
	int flag = 0;
	int num = 4 * n - 2;
	for(int i = 0; i < num; ++i){
		int tmp;
		cin >> tmp;
		int ss = 1;
		if(flag == 0){
			r1[tmp] = 1;
			flag = 1;
			for(int j = 0; j < card1.size(); ++j){
				if(card1[j] == tmp){
					card1.erase(card1.begin() + j);
					ss = 0;
					break;
				}
			}
			if(ss) card1.push_back(tmp);
		}
		else{
			r2[tmp] = 1;
			flag = 0;
			for(int j = 0; j < card2.size(); ++j){
				if(card2[j] == tmp){
					cout << j << " " << card2[j];
					card2.erase(card2.begin() + j);
					ss = 0;
					cout << " " << card2.size() << endl;
					break;
				}
			}
			if(ss) card2.push_back(tmp);
		}
	}
	flag = 0;
	while(!card1.empty() && !card2.empty()){
		++cnt;
		if(flag == 0){
			int tmp = card2[0];
			card2.erase(card2.begin());
			for(int i = 0; i < card1.size(); ++i){
				if(card1[i] == tmp) {
					card1.erase(card1.begin() + i);
					break;
				}
			}
			if(r1[tmp] != 1){
				r1[tmp] = 1;
				card1.push_back(tmp);
			}
		}
		else{
			int tmp = card1[0];
			card1.erase(card1.begin());
			for(int i = 0; i < card2.size(); ++i){
				if(card2[i] == tmp) {
					card2.erase(card2.begin() + i);
					break;
				}
			}
			if(r2[tmp] != 1){
				r2[tmp] = 1;
				card2.push_back(tmp);
			}
		}
	}
	cout << cnt << endl;
	return 0;
}