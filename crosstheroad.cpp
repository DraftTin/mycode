#include <iostream>

using namespace std;

void solution(int r, int y, int g, int n, int flag[], int t[]){
    // 小明上学
    int sum = 0;
    for(int i = 0; i < n; ++i){
        if(flag[i] == 2 ) sum += t[i] + r;
        else if(flag[i] != 3)sum += t[i];
    }
    cout << sum << endl;
}

int main(){
    int r, y, g;
    cin >> r >> y >> g;
    int n;
    cin >> n;
    int flag[100], t[100];
    for(int i = 0; i < n; ++i){
        cin >> flag[i] >> t[i];
    }
    solution(r, y, g, n, flag, t);
    return 0;
}