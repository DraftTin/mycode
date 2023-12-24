#include <iostream>
#include <cmath>

using namespace std;

int num = 0;

void solution(int board[8][8], int row, int verticalSlash[], int leftSlash[], int rightSlash[]){
	for(int i = 0; i < 8; ++i){
		int posR = row + i;
		int posL = row - i + 7;
		if(!verticalSlash[i] && !leftSlash[posL] && !rightSlash[posR]){
			if(row == 7){
				++num;
				continue;
			}
			board[row][i] = 1;
			verticalSlash[i] = 1;
			leftSlash[posL] = 1;
			rightSlash[posR] = 1;
			solution(board, row + 1, verticalSlash, leftSlash, rightSlash);
			board[row][i] = 0;
			verticalSlash[i] = 0;
			leftSlash[posL] = 0;
			rightSlash[posR] = 0;
		}
	}
}

bool hasPlace(int X[], int size, int k){
	for(int i = 0; i < k; ++i){
		// i和k表示第i+1个和第k+1个皇后 表示第i行和第k行
		// X[i]表示该状态下第i+1个皇后放置的列号, 若x1-y1=x2-y2或x1+y1=x2+y2成立则在同一slash上
		if(X[i] == X[k] || abs(X[i] - X[k]) == abs(i - k)){
			return false;
		}
	}
	return true;
}

void NQueensSolution(int n){
	int X[n] = {0};
	int k = 0;	// 表示从第一个皇后开始处理
	while(k >= 0){
		++X[k];
		while(X[k] <= n && !hasPlace(X, n, k)){
			// X[k]表示第 k+1个皇后检查的列值，用于检查k行, X[k]列是否可放置棋子,
			++X[k];
		}
		if(X[k] <= n){
			if(k == n - 1){
				++num;
			}
			else{
				++k;
				X[k] = 0;
			}
		}
		else{
			--k;	// 回溯
		}
	}
}

int main(){
	// int board[8][8] = {0};
	// int row = 0;
	// int verticalSlash[8] = {0};
	// int leftSlash[15] = {0};
	// int rightSlash[15] = {0};
	// solution(board, row, verticalSlash, leftSlash, rightSlash);
	NQueensSolution(10);
	cout << num << endl;
	return 0;
}