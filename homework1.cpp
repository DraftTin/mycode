#include <iostream>
#include <map>
#include <set>
#include <cmath>
#include <iomanip>

using namespace std;

const double epsilon = 10e-12;
const double b = 0.16;
const double c = -0.064;

struct Matrix {
	map<pair<int, int>, double> matrix;
	void set(int row, int col, double value) {
		matrix[{row, col}] = value;
	};
	double get(int row, int col) {
		if (matrix.count({row, col}) == 0) {
			return 0.0;
		}
		else {
			return matrix[{row, col}];
		}
	};
	void clear() {
		matrix.clear();
	};
	void copy(Matrix* A) {
		matrix.insert(A->matrix.begin(), A->matrix.end());
	};
};

struct Vector {
	map<int, double> vector;
	void set(int index, double value) {
		vector[index] = value;
	};
	double get(int index) {
		if (vector.count(index) == 0) {
			return 0.0;
		}
		else {
			return vector[index];
		}
	};
	void clear() {
		vector.clear();
	};
	void copy(Vector* A) {
		vector.insert(A->vector.begin(), A->vector.end());
	};
};

bool approximatelyZero(double a) {
	if (a <= epsilon && a >= - epsilon) {
		return true;
	}
	return false;
}

void initA(Matrix* A) {
	// input ai
	for (int i = 1; i <= 501; i++) {
		double j = i;
		double ai = (1.64 - 0.024 * j) * sin(0.2 * j) - 0.64 * exp(0.1 / j);
		// cout << ai << "\n";
		A->set(i, i, ai);
	}
	// input b
	for (int i = 1; i + 1 <= 501; i++) {
		A->set(i, i + 1, b);
		A->set(i + 1, i, b);
	}
	// input c
	for (int i = 1; i + 2 <= 501; i++) {
		A->set(i, i + 2, c);
		A->set(i + 2, i, c);
	}
}

void matrixMvector(Matrix* M, Vector* V, Vector* ans, int begin, int end, double avg, bool turn) {
	for (int i = begin; i <= end; i++) {
		double tmp = 0;
		for (int j = begin; j <= end; j++) {
			if (turn) {
				if (M->get(j, i) != 0 && V->get(j) != 0) {
					tmp += M->get(j, i) * V->get(j);
				}
			}
			else {
				if (M->get(i, j) != 0 && V->get(j) != 0) {
					tmp += M->get(i, j) * V->get(j);
				}
			}
		}
		tmp /= avg;
		ans->set(i, tmp);
	}
	return;
}

void vectorMvector1(Vector* V1, Vector* V2, int begin, int end, double avg, double* ans) {
	*ans = 0;
	for (int i = begin; i <= end; i++) {
		*ans += V1->get(i) * V2->get(i);
	}
	*ans /= avg;
	return;
}

void vectorMvector2(Vector* V1, Vector* V2, int begin, int end, Matrix* ans) {
	ans->clear();
	for (int i = begin; i <= end; i++) {
		for (int j = begin; j <= end; j++) {
			ans->set(i, j, V1->get(i) * V2->get(j));
		}
	}
	return;
}

void numTvector(double times, Vector* V, int begin, int end, Vector* ans) {
	for (int i = begin; i <= end; i++) {
		double tmp = V->get(i);
		if (tmp != 0) {
			ans->set(i, times * tmp);
		}
	}
	return;
}

void vectorAvector(Vector* V1, Vector* V2, int begin, int end, bool negative, Vector* ans) {
	ans->clear();
	for (int i = begin; i <= end; i++) {
		double tmp1 = V1->get(i);
		double tmp2 = V2->get(i);
		if (negative) {
			tmp1 -= tmp2;
		}
		else {
			tmp1 += tmp2;
		}
		if (!approximatelyZero(tmp1)) {
			ans->set(i, tmp1);
		}
	}
	return;
}

void matrixAmatrix(Matrix* M1, Matrix* M2, int begin, int end, bool negative, Matrix* ans) {
	ans->clear();
	for (int i = begin; i <= end; i++) {
		for (int j = begin; j <= end; j++) {
			double tmp1 = M1->get(i, j);
			double tmp2 = M2->get(i, j);
			if (negative) {
				tmp1 -= tmp2;
			}
			else {
				tmp1 += tmp2;
			}
			if (!approximatelyZero(tmp1)) {
				ans->set(i, j, tmp1);
			}
		}
	}
	return;
}

Matrix quasiUpperTriangulation(Matrix* A, int n) {
	Matrix tmp[2];
	tmp[0].copy(A);
	int r;
	for (r = 1; r <= n - 2; r++) {
		cout << tmp[!(r % 2)].get(r + 2, r) << " ";
		// (1)
		bool allZero = true;
		for (int i = r + 2; i <= n; i++) {
			if (!approximatelyZero(tmp[!(r % 2)].get(i,  r))) {
				allZero = false;
				break;
			}
		}
		if (allZero) {
			tmp[r % 2].clear();
			tmp[r % 2].copy(&(tmp[!(r % 2)]));
			continue;
		}
		// (2)
		double d = 0;
		for (int i = r + 1; i <= n; i++) {
			double a_ir = tmp[!(r % 2)].get(i, r);
			if (a_ir != 0) {
				d += pow(a_ir, 2);
			}
		}
		d = sqrt(d);
		double a_rr = tmp[!(r % 2)].get(r + 1, r);
		if (a_rr > 0) {
			d = -d;
		}
		double h = pow(d, 2) - d * a_rr; 
		// (3)
		Vector u;
		u.set(r + 1, a_rr - d);
		for (int i = r + 2; i <= n; i++) {
			double a_ir = tmp[!(r % 2)].get(i, r);
			if (a_ir != 0) {
				u.set(i, a_ir);
			}
		}
		// (4)
		Vector p; 
		matrixMvector(&(tmp[!(r % 2)]), &u, &p, 1, n, h, true);
		Vector q;
		matrixMvector(&(tmp[!(r % 2)]), &u, &p, 1, n, h, false);
		double t;
		vectorMvector1(&p, &u, 1, n, h, &t);
		Vector w0;
		numTvector(t, &u, 1, n, &w0);
		Vector w1;
		vectorAvector(&q, &w0, 1, n, true, &w1);
		Matrix m0, m1, m2;
		vectorMvector2(&w1, &u, 1, n, &m0);
		cout << setprecision(12) << m0.get(r + 2, r) << " ";
		vectorMvector2(&u, &p, 1, n, &m1);
		cout << setprecision(12) << m0.get(r + 2, r) << " ";
		matrixAmatrix(&(tmp[!(r % 2)]), &m0, 1, n, true, &m2);
		matrixAmatrix(&m2, &m1, 1, n, true, &(tmp[r % 2]));
		cout << setprecision(12) << tmp[r % 2].get(r + 2, r) << "\n";
	}
	return tmp[r % 2];
}

int main(int argc, char** argv) {
	Matrix A;
	initA(&A);
	quasiUpperTriangulation(&A, 6);
	return 0;
}