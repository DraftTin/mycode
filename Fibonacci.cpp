#include <iostream>
#include <vector>
#include <time.h>
#include <thread>

using namespace std;

class Matrix{
public:
	long long a, b, c, d;
	Matrix(long long aa, long long bb, long long cc, long long dd) : a(aa), b(bb), c(cc), d(dd) {}
	Matrix() : a(0), b(0), c(0), d(0) {}
};

Matrix Matrix_multiplication(Matrix& A, Matrix& B){
	Matrix C;
	C.a = A.a * B.a + A.b * B.c;
	C.b = A.a * B.b + A.b * B.d;
	C.c = A.c * B.a + A.d * B.c;
	C.d = A.c * B.b + A.d * B.d;
	return C;
}

Matrix Matrix_pow(Matrix& matrix, int n){
	if(n == 1)
		return matrix;
	if(n % 2 == 0){
		Matrix temp = Matrix_pow(matrix, n / 2);
		return Matrix_multiplication(temp, temp);
	}
	Matrix temp = Matrix_pow(matrix, (n - 1) / 2);
	Matrix t1(Matrix_multiplication(temp, temp));
	Matrix t2(1,1,1,0);
	return Matrix_multiplication(t1, t2);
}

long long Fibonacci(int n){
	if(n == 0 || n == 1)
		return 1;
	Matrix matrix(1,1,1,0);
	Matrix t1(Matrix_pow(matrix, n-1));
	Matrix t2(1,0,1,0);
	return Matrix_multiplication(t1, t2).a;
}

long long Fibonacci_with_recursion(int n){
	if(n == 0 || n == 1)
		return 1;
	return Fibonacci_with_recursion(n-1) + Fibonacci_with_recursion(n-2);
}

long long Fibonacci_without_recursion(int n){
	long long cur = 1, pre = 1;
	for(int i = 2; i <= n; ++i){
		long long tmp = cur;
		cur += pre;
		pre = tmp;
	}
	return cur;
}

void Fibonacci_with_parallel(int n, long long& x){
	if(n == 1 || n == 0){
		x = 1;
		return ;
	}
	long long x1, x2;
	thread t1(Fibonacci_with_parallel, n-1, ref(x1));
	thread t2(Fibonacci_with_parallel, n-2, ref(x2));
	t1.join();
	t2.join();
	x = x1 + x2;
}

int main(void){
	int n;
	cin >> n;
	clock_t start = clock();
	cout << Fibonacci(n) << endl;
	clock_t end = clock();
	cout << "logN Cost " << double(end - start) / CLOCKS_PER_SEC << " sec" << endl << endl;
	start = clock();
	cout << Fibonacci_without_recursion(n) << endl;
	end = clock();
	cout << "n Cost " << double(end - start) / CLOCKS_PER_SEC << " sec" << endl << endl;
	
	start = clock();
	cout << Fibonacci_with_recursion(n) << endl;
	end = clock();
	cout << "2^n Cost " << double(end - start) / CLOCKS_PER_SEC << " sec" << endl << endl;

	if(n > 20)
		return 0;
	start = clock();
	long long x;
	Fibonacci_with_parallel(n, x);
	cout << x << endl;
	end = clock();
	cout << "parallel Cost " << double(end - start) / CLOCKS_PER_SEC << " sec" << endl << endl;
	return 0;
}