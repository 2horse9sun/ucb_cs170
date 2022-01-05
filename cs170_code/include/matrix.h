#ifndef matrix_
#define matrix_
#include<iostream>
using namespace std;

template<class T>
class Matrix {
public:
	T** element;
	int row_size;
	int col_size;

	Matrix() {}

	Matrix(int row_size, int col_size) {
		if (row_size < 0 || col_size < 0)
			throw "row_size and col_size are positive!";
		if ((row_size == 0 || col_size == 0) && (row_size != 0 || col_size != 0))
			throw "Invalid params!";
		this->row_size = row_size;
		this->col_size = col_size;
		element = new T * [row_size];
		for (int i = 0; i < row_size; i++) {
			element[i] = new T[col_size];
		}
	}

	Matrix(int row_size, int col_size, T val) {
		if (row_size < 0 || col_size < 0)
			throw "row_size and col_size are positive!";
		if ((row_size == 0 || col_size == 0) && (row_size != 0 || col_size != 0))
			throw "Invalid params!";
		this->row_size = row_size;
		this->col_size = col_size;
		element = new T * [row_size];
		for (int i = 0; i < row_size; i++) {
			element[i] = new T[col_size];
		}
		for (int i = 0; i < row_size; i++) {
			for (int j = 0; j < col_size; j++) {
				element[i][j] = val;
			}
		}
	}


	Matrix(const Matrix<T>& m) {
		row_size = m.row_size;
		col_size = m.col_size;
		element = new T * [row_size];
		for (int i = 0; i < row_size; i++) {
			element[i] = new T[col_size];
		}
		for (int i = 0; i < row_size; i++) {
			for (int j = 0; j < col_size; j++) {
				element[i][j] = m.element[i][j];
			}
		}
	}

	~Matrix() {
		for (int i = 0; i < row_size; i++) {
			delete[] element[i];
		}
		delete[] element;
	}

	T& operator()(int i, int j) {
		if (i < 1 || i > row_size|| j < 1 || j > col_size)
			throw "out of index!";
		return element[i - 1][j - 1];
	}

	Matrix<T>& operator=(const Matrix<T>& m) {
		if (this != &m) {
			for (int i = 0; i < row_size; i++) {
				delete[] element[i];
			}
			delete[] element;
			row_size = m.row_size;
			col_size = m.col_size;
			element = new T * [row_size];
			for (int i = 0; i < row_size; i++) {
				element[i] = new T[col_size];
			}
			for (int i = 0; i < row_size; i++) {
				for (int j = 0; j < col_size; j++) {
					element[i][j] = m.element[i][j];
				}
			}
		}
		return *this;
	}

	Matrix<T> operator+(const Matrix<T>& m) {
		if (row_size != m.row_size || col_size != m.col_size)
			throw "Dimension not match!";
		Matrix<T> res(row_size, col_size);
		for (int i = 0; i < row_size; i++) {
			for (int j = 0; j < col_size; j++) {
				res.element[i][j] = element[i][j] + m.element[i][j];
			}
		}
		return res;
	}

	Matrix<T> operator-(const Matrix<T>& m) {
		if (row_size != m.row_size || col_size != m.col_size)
			throw "Dimension not match!";
		Matrix<T> res(row_size, col_size);
		for (int i = 0; i < row_size; i++) {
			for (int j = 0; j < col_size; j++) {
				res.element[i][j] = element[i][j] - m.element[i][j];
			}
		}
		return res;
	}

	Matrix<T> operator-() {
		Matrix<T> res(row_size, col_size);
		for (int i = 0; i < row_size; i++) {
			for (int j = 0; j < col_size; j++) {
				res.element[i][j] = -element[i][j];
			}
		}
		return res;
	}

	Matrix<T> multiply(Matrix<T>& X, Matrix<T>& Y) {
		Matrix<T> res(X.row_size, Y.col_size);
		for (int i = 0; i < X.row_size; i++) {
			for (int j = 0; j < Y.col_size; j++) {
				T val = 0;
				for (int k = 0; k < X.col_size; k++) {
					val += X.element[i][k] * Y.element[k][j];
				}
				res.element[i][j] = val;
			}
		}
		return res;
	}

	// Strassen
	Matrix<T> multiply2(Matrix<T>& X, Matrix<T>& Y) {
		if (X.row_size == 1 && X.col_size == 1 && Y.row_size == 1 && Y.col_size == 1) {
			Matrix<T> res(1, 1, X(1, 1) * Y(1, 1));
			return res;
		}

		int X_block_row_size = X.row_size % 2 == 0 ? X.row_size / 2 : X.row_size / 2 + 1;
		int X_block_col_size = X.col_size % 2 == 0 ? X.col_size / 2 : X.col_size / 2 + 1;
		int Y_block_row_size = Y.row_size % 2 == 0 ? Y.row_size / 2 : Y.row_size / 2 + 1;
		int Y_block_col_size = Y.col_size % 2 == 0 ? Y.col_size / 2 : Y.col_size / 2 + 1;
		Matrix<T> A(X_block_row_size, X_block_col_size, 0);
		Matrix<T> B(X_block_row_size, X_block_col_size, 0);
		Matrix<T> C(X_block_row_size, X_block_col_size, 0);
		Matrix<T> D(X_block_row_size, X_block_col_size, 0);
		Matrix<T> E(Y_block_row_size, Y_block_col_size, 0);
		Matrix<T> F(Y_block_row_size, Y_block_col_size, 0);
		Matrix<T> G(Y_block_row_size, Y_block_col_size, 0);
		Matrix<T> H(Y_block_row_size, Y_block_col_size, 0);
		for (int i = 1; i <= X.row_size; ++i) {
			for (int j = 1; j <= X.col_size; ++j) {
				if (i <= X_block_row_size && j <= X_block_col_size) A(i, j) = X(i, j);
				else if (i <= X_block_row_size && j > X_block_col_size) B(i, j-X_block_col_size) = X(i, j);
				else if (i > X_block_row_size && j <= X_block_col_size) C(i-X_block_row_size, j) = X(i, j);
				else D(i-X_block_row_size, j-X_block_col_size) = X(i, j);
			}
		}
		for (int i = 1; i <= Y.row_size; ++i) {
			for (int j = 1; j <= Y.col_size; ++j) {
				if (i <= Y_block_row_size && j <= Y_block_col_size) E(i, j) = Y(i, j);
				else if (i <= Y_block_row_size && j > Y_block_col_size) F(i, j-Y_block_col_size) = Y(i, j);
				else if (i > Y_block_row_size && j <= Y_block_col_size) G(i-Y_block_row_size, j) = Y(i, j);
				else H(i-Y_block_row_size, j-Y_block_col_size) = Y(i, j);
			}
		}
		
		Matrix<T> FH = F - H; Matrix<T> P1 = multiply2(A, FH);
		Matrix<T> AB = A + B; Matrix<T> P2 = multiply2(AB, H);
		Matrix<T> CD = C + D; Matrix<T> P3 = multiply2(CD, E);
		Matrix<T> GE = G - E; Matrix<T> P4 = multiply2(D, GE);
		Matrix<T> AD = A + D; Matrix<T> EH = E + H; Matrix<T> P5 = multiply2(AD, EH);
		Matrix<T> BD = B - D; Matrix<T> GH = G + H; Matrix<T> P6 = multiply2(BD, GH);
		Matrix<T> AC = A - C; Matrix<T> EF = E + F; Matrix<T> P7 = multiply2(AC, EF);
		Matrix<T> XY1 = P5 + P4 - P2 + P6;
		Matrix<T> XY2 = P1 + P2;
		Matrix<T> XY3 = P3 + P4;
		Matrix<T> XY4 = P1 + P5 - P3 - P7;
		Matrix<T> res(X.row_size, Y.col_size);
		for (int i = 1; i <= X.row_size; ++i) {
			for (int j = 1; j <= Y.col_size; ++j) {
				if (i <= X_block_row_size && j <= Y_block_col_size) res(i, j) = XY1(i, j);
				else if (i <= X_block_row_size && j > Y_block_col_size) res(i, j) = XY2(i, j-Y_block_col_size);
				else if (i > X_block_row_size && j <= Y_block_col_size) res(i, j) = XY3(i-X_block_row_size, j);
				else res(i, j) = XY4(i-X_block_row_size, j-Y_block_col_size);
			}
		}
		return res;
 	}

	Matrix<T> operator*(Matrix<T>& m) {
		return multiply2(*this, m);
	}

	Matrix<T> operator*(T val) {
		Matrix<T> res(row_size, col_size);
		for (int i = 0; i < row_size; i++) {
			for (int j = 0; j < col_size; j++) {
				res.element[i][j] = val * element[i][j];
			}
		}
		return res;
	}

	Matrix<T> operator/(T val) {
		if (val == 0) {
			throw "divisor 0";
		}
		Matrix<T> res(row_size, col_size);
		for (int i = 0; i < row_size; i++) {
			for (int j = 0; j < col_size; j++) {
				res.element[i][j] = element[i][j] / val;
			}
		}
		return res;
	}

	Matrix<T> transpose() {
		Matrix<T> res(col_size, row_size);
		for (int i = 0; i < col_size; i++) {
			for (int j = 0; j < row_size; j++) {
				res.element[i][j] = element[j][i];
			}
		}
		return res;
	}


	pair<Matrix<T>, Matrix<T>> LU_factorization() {
		Matrix<T> L(row_size, col_size, 0);
		Matrix<T> U(row_size, col_size, 0);
		for (int i = 0; i < row_size; i++) {
			for (int j = i; j < col_size; j++) {
				T sum = 0;
				for (int k = 0; k < i; k++) {
					sum += L.element[i][k] * U.element[k][j];
				}
				U.element[i][j] = element[i][j] - sum;

			}

			for (int j = i + 1; j < row_size; j++) {
				T sum = 0;
				for (int k = 0; k < i; k++) {
					sum += L.element[j][k] * U.element[k][i];
				}
				L.element[j][i] = (element[j][i] - sum) / U.element[i][i];
			}
			L.element[i][i] = 1;
		}
		return make_pair(L, U);
	}

	Matrix<T> inverse() {
		pair<Matrix<T>, Matrix<T>> res = this->LU_factorization();
		Matrix<T> L = res.first;
		Matrix<T> U = res.second;
		Matrix<T> inversedL(row_size, col_size, 0);
		Matrix<T> inversedU(row_size, col_size, 0);
		for (int i = 0; i < col_size; i++) {
			for (int j = 0; j < row_size; j++) {
				if (i == j) {
					if (L.element[i][i] == 0) {
						throw "Not exist!";
					}
					inversedL.element[i][j] = 1 / L.element[i][i];
				}
				else if (i < j) {
					inversedL.element[i][j] = 0;
				}
				else {
					T sum = 0;
					for (int k = j; k < i; k++) {
						sum += L.element[i][k] * inversedL.element[k][j];
					}
					if (L.element[i][i] == 0) {
						throw "Not exist!";
					}
					inversedL.element[i][j] = -sum / L.element[i][i];
				}
			}
		}
		for (int p = 0; p < col_size; p++) {
			for (int i = 0; i < row_size - p; i++) {
				int j = i + p;
				if (i == j) {
					if (U.element[i][i] == 0) {
						throw "Not exist!";
					}
					inversedU.element[i][j] = 1 / U.element[i][i];
				}
				else {
					T sum = 0;
					for (int k = j; k > i; k--) {
						sum += U.element[i][k] * inversedU.element[k][j];
					}
					if (U.element[i][i] == 0) {
						throw "Not exist!";
					}
					inversedU.element[i][j] = -sum / U.element[i][i];
				}
			}
		}
		return inversedU * inversedL;
	}

	template<class T>
	friend ostream& operator<<(ostream& out, const Matrix<T>& m) {
		for (int i = 0; i < m.row_size; i++)
		{
			for (int j = 0; j < m.col_size; j++)
				out << m.element[i][j] << " ";
			out << endl;
		}
		return out;
	}

};



#endif
