#include <iostream>
#include <thread>
#include <vector>
#include <time.h>
#include <stdlib.h>

using namespace std;


vector<int> MAT_VEC(vector<vector<int>>& A, vector<int>& x){
	//不能单独并行y[i] += A[i][j] * x[j]; 语句之间存在确定性竞争, 可能会出现错误
	vector<int> y(A.size(), 0);
	vector<thread> workers;
	for(int i = 0; i < A.size(); ++i){
		workers.push_back(thread([i, A, &y, x](){
			for(int j = 0; j < x.size(); ++j){
				y[i] += A[i][j] * x[j];
			}
		}));
	}
	for(vector<thread>::iterator t = workers.begin(); t != workers.end(); ++t)
		t->join();
	return y;
}

vector<vector<int>> P_Sqare_Matrix_Multiply(vector<vector<int>>& A, vector<vector<int>>& B){
	vector<vector<int>> C(A.size(), vector<int>(B[0].size(), 0));
	vector<thread> workers1;
	for(int i = 0; i < A.size(); ++i){
		workers1.push_back(thread([A, B, &C, i](){
			vector<thread> workers2;
			for(int j = 0; j < B[0].size(); ++j){
				workers2.push_back(thread([A, B, &C, i, j](){
					for(int k = 0; k < A[0].size(); ++k)
						C[i][j] += A[i][k] * B[k][j];
				}));
			}
			for(vector<thread>::iterator t = workers2.begin(); t != workers2.end(); ++t)
				t->join();
		}));
	}
	for(vector<thread>::iterator t = workers1.begin(); t != workers1.end(); ++t)
		t->join();
	return C;
}

vector<vector<int>> Sqare_Matrix_Multiply(vector<vector<int>>& A, vector<vector<int>>& B){
	vector<vector<int>> C(A.size(), vector<int>(B[0].size(), 0));
	for(int i = 0; i < A.size(); ++i){
		for(int j = 0; j < B[0].size(); ++j){
			for(int k = 0; k < A[0].size(); ++k)
				C[i][j] += A[i][k] * B[k][j];
		}
	}
	return C;
}



int main(){
	int n;
	cin >> n;
	vector<vector<int>> A(n, vector<int>(n));
	vector<vector<int>> B(n, vector<int>(n));
	srand((unsigned)time(NULL));
	for(int i = 0; i < A.size(); ++i){
		for(int j = 0; j < A[0].size(); ++j){
			A[i][j] = rand() % 100;
			B[i][j] = rand() % 100;
		}
	}
	clock_t start = clock();
	vector<vector<int>> y = P_Sqare_Matrix_Multiply(A, B);
	clock_t end = clock();
	cout << "Parallel algo costs " << double(end - start) / CLOCKS_PER_SEC << " sec" << endl;
	clock_t s = clock();
	vector<vector<int>> yy = Sqare_Matrix_Multiply(A, B);
	clock_t e = clock();
	cout << "ordinary algo costs " << double(e - s) / CLOCKS_PER_SEC << " sec" << endl;
	return 0;
}