#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 三元组(val, row, col)存储稀疏矩阵
// 矩阵存储在三元组数组中, 用类封装
// transpose: 不断遍历数组, 每次遍历将对应列值的三元组取出, 作为新的行值存储在新的数组中, 由于原数组是按行数和列数递增的顺序存储的, 所以新数组自动地按列数和行数递增存储
// Time of transpose: 遍历整个数组n次, O(n^2), 对于稀疏矩阵, 为O(row^2), 和用二维数组存储的矩阵转置的时间复杂度相同
template <typename T>
class Node{
public:
    Node(T v, int r, int c) : val(v), row(r), col(c) {}
    T val;
    int row;
    int col;
};

template <typename T>
class Matrix{
public:
    explicit Matrix(vector<Node<T>> copy, int row_size_) : items(copy), row_size(row_size_) {}
    Node<T>& operator[](int i) { return items[i]; }
    int size() {return items.size();}
    int rowSize() {return row_size;}
private:
    int row_size;
    vector<Node<T>> items;
};

template <typename T>
void Transpose(Matrix<T> &Mat){
    vector<Node<T>> items;
    for(int i = 0; i < Mat.size(); ++i){
        for(int j = 0; j < Mat.size(); ++j){
            if(Mat[j].col == i){
                items.push_back(Node<T>(Mat[j].val, Mat[j].col, Mat[j].row));
            }
        }
    }
    Matrix<T> copy(items, Mat.rowSize());
    Mat = copy;
}

template <typename T>
void show(Matrix<T> Mat){
    cout << endl;
	int count = 0;
	for(int i = 0; i < Mat.rowSize(); ++i){
		for(int j = 0; j < Mat.rowSize(); ++j){
			if(Mat[count].row == i && Mat[count].col == j){
				cout << Mat[count].val << " ";
				++count;
			}
			else
				cout << 0 << " ";
		}
		cout << endl;
	}
}

template <typename T>
Matrix<T> createMatrix(vector<Node<T>>& matrix, int row_size_){
    Matrix<T> Mat(matrix, row_size_);   
    return Mat;
}

int main(void){
    int n;
    cout << "input the Rows of matrix: ";
    cin >> n;
    vector<Node<int>> matrix;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            int val;
            cin >> val;
            if(val != 0){
                matrix.push_back(Node<int>(val, i, j));
            }
        }
    }
    Matrix<int> Mat = createMatrix(matrix, n);
    show(Mat);
    Transpose(Mat);
    cout << endl;
    show(Mat);
    return 0;
}
