#include <iostream>

using namespace std;

int solution(int p[], int n){
    // 动态规划矩阵链乘积问题
    int m[100][100] = {0};   // m[i][j]标识矩阵i到矩阵j乘积链的最少次数
    int pos[100][100] = {0}; // pos[i][j]记录矩阵i到矩阵j乘积链的括号的分割位置
    for(int i = 1; i < n; ++i){
        // i记录矩阵乘积链的长度
        for(int j = 1; j <= n - i; ++j){
            int minVal = INT_MAX;
            int minIndex = -1;
            for(int k = j; k < j + i; ++k){
                int val = m[j][k] + m[k + 1][j + i] + p[j - 1] * p[k] * p[j + i];
                if(val < minVal){
                    minVal = val;
                    minIndex = j;
                }
            }
            m[j][j + i] = minVal;
            pos[j][j + i] = minIndex;
        }
    }
    return m[1][n];
}

int main(){
    int n;
    cin >> n;
    int p[100];
    for(int i = 0; i <= n; ++i) cin >> p[i];
    int minTimes = solution(p, n);
    cout << minTimes << endl;
    return 0;
}