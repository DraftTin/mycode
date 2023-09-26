#include <iostream>
#include <vector>

using namespace std;

// 最优二叉搜索树
// 输入成功检索的概率P 失败检索的概率Q 返回最优二叉检索树 用二维数组R来表示 R[i][j]表示a[i + 1] ~ a[j]的根节点
void solution(vector<int>& P, vector<int>& Q, int n, vector<vector<int>>& R, vector<vector<int>>& C){
	// 算法：动态规划求解，R[i][j]表示叶节点下标从i到j的根节点下标，C[i][j]表示叶节点下标从i到j的代价
	// 其中C[i][j] = min{C[i][k - 1] + C[k][j] + W[i][j]}, W[i][j] = Q[i] + sigma_(k = i + 1 to j)(Q[k] + P[k])
	// 时间复杂度经Knuth优化后由O(n^3)->O(n^2)
	vector<vector<int>> W(n + 1, vector<int>(n + 1));
	for(int i = 0; i < n; ++i){
		R[i][i] = 0;
		W[i][i] = Q[i];
		C[i][i] = 0;
		// 注： 此处对R[i][i + 1], W[i][i + 1], C[i][i + 1]赋值时必要的，因为下面的循环初始化m = 2,m不能初始化为1，因为R[i][i] = 0，会在循环中将R[i][j]赋值为0
		R[i][i + 1] = i + 1;
		W[i][i + 1] = Q[i] + Q[i + 1] + P[i + 1]; // 只有一个节点时 该节点为根节点
		C[i][i + 1] = Q[i] + Q[i + 1] + P[i + 1]; // 因为C[i][i]和C[i+1][i+1]都为0
		// cout << i << " " << i + 1 << " " << R[i][i + 1] << endl;
	}	
	R[n][n] = 0;
	W[n][n] = Q[n];
	C[n][n] = 0;
	for(int m = 2; m <= n; ++m){
		for(int i = 0; i <= n - m; ++i){
			int j = i + m;
			// cout << i << " " << j << endl;
			W[i][j] = W[i][j - 1] + Q[j] + P[j]; // W[i][j] = Q[i] + sigma_(k = i + 1 to j)(P[k] + Q[k])可得出该等式
			int minVal = INT_MAX;
			int r = -1;
			// cout << R[i][j - 1] << " " << R[i + 1][j] << " " << i << " " << j - 1 << " " << i + 1 << " " << j << endl;
			for(int k = R[i][j - 1]; k <= R[i + 1][j]; ++k){
				int val = C[i][k - 1] + C[k][j] + W[i][j];
				if(val < minVal){
					minVal = val;
					r = k;
				}
			}
			R[i][j] = r;
			C[i][j] = minVal;
		}
	}
	cout << "W: " << endl;
	for(int i = 0; i < n + 1; ++i){
		for(int j = 0; j < n + 1; ++j){
			cout << W[i][j] << " ";
		}
		cout << endl;
	}
	cout << "R: " << endl;
	for(int i = 0; i < n + 1; ++i){
		for(int j = 0; j < n + 1; ++j){
			cout << R[i][j] << " ";
		}
		cout << endl;
	}
	cout << "C: " << endl;
	for(int i = 0; i < n + 1; ++i){
		for(int j = 0; j < n + 1; ++j){
			cout << C[i][j] << " ";
		}
		cout << endl;
	}
}


int main(){
	int n;
	cin >> n;
	vector<vector<int>> R(n + 1, vector<int>(n + 1)); // 用来表示区间段的根节点
	vector<vector<int>> C(n + 1, vector<int>(n + 1)); // 用来表示区间段的代价
	vector<int> P(n + 1); // 从1开始
	vector<int> Q(n + 1); // 从0开始
	for(int i = 1; i < n + 1; ++i){
		cin >> P[i];
	}
	for(int i = 0; i < n + 1; ++i){
		cin >> Q[i];
	}
	solution(P, Q, n, R, C);
	// cout << "R: " << endl;
	// for(int i = 0; i < n + 1; ++i){
	// 	for(int j = 0; j < n + 1; ++j){
	// 		cout << R[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << "cost = " << C[0][n] << endl;
	return 0;
}

/*
4
3 3 1 1
2 3 1 1 1
*/