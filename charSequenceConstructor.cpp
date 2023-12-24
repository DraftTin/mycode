#include <iostream>
#include <string>
#include <vector>

using namespace std;

int count = 0;

bool check(string& s, int pos, int L){
    // 每次检测以pos为最后一位的子序列和该子序列前一个子序列是否相同
    int i = pos - L + 1;
    int j = i - L;
    if(j < 0 || i < 0) return true; 
    int tmp = 0;
    while(tmp < L && s[i + tmp] == s[j + tmp]) ++tmp;

    if(tmp == L) return false;

    return true;
}

void solution(vector<char>& charSet, string& s, int n, int L, int pos){
    // charSet表示字符集   n表示构造字符序列的长度   L表示子串的长度
    if(pos == n){
        cout << s << endl;
        ++count;
        return ;
    }
    for(int i = 0; i < charSet.size(); ++i){
        s[pos] = charSet[i];
        if(check(s, pos, L)){
            solution(charSet, s, n, L, pos + 1);
        }
    }
}

int main(){
    vector<char> charSet = {'A', 'B', 'C'};
    int n;
    cin >> n;
    int L;
    cin >> L;
    string s(n, 'A');
    solution(charSet, s, n, L, 0);
    cout << "count = " << count << endl;
    return 0;
}






