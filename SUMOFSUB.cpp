#include <iostream>

using namespace std;


void SUMOFSUB(int s, int k, int r, int target, int W[], int size, int X[]){
    // 子集和数问题
    // s表示按照当前方案子集的和，k表示处理到下标为k的元素
    // r表示接下来(k <= i <= n - 1，初始下标为0)的所有W[i]的和
    // 限界函数：s + r >= target && s + W[k] + W[k + 1] <= target 生成左子树
    //          s + r - W[k] >= target && s + W[k + 1] <= target  生成右子树 
    X[k] = 1;
    if(s + W[k] == target){
        for(int i = 0; i < size; ++i){
            cout << X[i] << " ";
        }
        cout << endl;
    }
    else if(k + 1 < size && s + W[k] + W[k + 1] <= target){
        SUMOFSUB(s + W[k], k + 1, r - W[k], target, W, size, X);
    }
    X[k] = 0;
    if(k + 1 < size && s + r - W[k] >= target && s + W[k + 1] <= target){
        SUMOFSUB(s, k + 1, r - W[k], target, W, size, X);
    }
}

int main(){
    int size;
    cin >> size;
    int W[99] = {0};
    int sum = 0;
    for(int i = 0; i < size; ++i){
        cin >> W[i];
        sum += W[i];
    }
    int target;
    cin >> target;
    int X[99] = {0};
    if(sum >=  target) {
        SUMOFSUB(0, 0, sum, target, W, size, X);
    }
    return 0;
}









// void sumofsub(int s, int r, int k, int target, int W[], int n, int X[]){
//     if(k == n) return ;
//     if(s + W[k] == target){
//         X[k] = 1;
//         for(int i = 0; i < n; ++i) cout << X[i] << " ";
//         cout << endl;
//     }
//     else if(s + W[k] > target || s + r < target) return ;
//     else{
//         X[k] = 1;
//         sumofsub(s + W[k], r - W[k], k + 1, target, W, n, X);
//     }
//     X[k] = 0;
//     sumofsub(s, r - W[k], k + 1, target, W, n, X);
// }