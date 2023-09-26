#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 最长公共子序列问题
int findLCS(string& s1, string& s2){
    // 算法效率分析：初始赋值2n，然后对A[][]赋值m * n，总时间复杂度O(m * n)
    // 可以用一个dir[][]记录路径，如1表示取A[i][j - 1], -1表示A[i - 1][j], 0表示为选中处
    vector<vector<int>> A(s1.size(), vector<int>(s2.size(), 0)); // A[i][j]表示s1[0]~s1[i]字符串和s2[0]~s2[j]字符串的最长公共子序列长度
    int i = 0;
    int j = 0;
    A[0][0] = s1[0] == s2[0] ? 1 : 0;
    for(int i = 1; i < s1.size(); ++i){
        if(s1[i] == s2[0]) A[i][0] = 1;
        else A[i][0] = A[i - 1][0];
    }
    for(int i = 1; i < s2.size(); ++i){
        if(s2[i] == s1[0]) A[0][i] = 1;
        else A[0][i] = A[0][i - 1];
    }
    for(int i = 1; i < s1.size(); ++i){
        for(int j = 1; j < s2.size(); ++j){
            if(s1[i] == s2[j]) A[i][j] = A[i - 1][j - 1] + 1;
            else{
                A[i][j] = max(A[i][j - 1], A[i - 1][j]);
            }
        }
    }
    return A[s1.size() - 1][s2.size() - 1];
}

int main(){
    string s1;
    cin >> s1;
    string s2;
    cin >> s2;
    cout << findLCS(s1, s2) << endl;
    return 0;
}