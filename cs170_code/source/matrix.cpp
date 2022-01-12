#include<iostream>
#include "../include/matrix.h"
using namespace std;


Matrix::Matrix(int row_size, int col_size) {
	if (row_size < 0 || col_size < 0)
		throw "row_size and col_size are positive!";
	if ((row_size == 0 || col_size == 0) && (row_size != 0 || col_size != 0))
		throw "Invalid params!";
	this->row_size = row_size;
	this->col_size = col_size;
	element = new int * [row_size];
	for (int i = 0; i < row_size; i++) {
		element[i] = new int[col_size];
	}
}


Matrix::Matrix(int row_size, int col_size, int val) {
	if (row_size < 0 || col_size < 0)
		throw "row_size and col_size are positive!";
	if ((row_size == 0 || col_size == 0) && (row_size != 0 || col_size != 0))
		throw "Invalid params!";
	this->row_size = row_size;
	this->col_size = col_size;
	element = new int * [row_size];
	for (int i = 0; i < row_size; i++) {
		element[i] = new int[col_size];
	}
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			element[i][j] = val;
		}
	}
}


Matrix::Matrix(const Matrix& m) {
	row_size = m.row_size;
	col_size = m.col_size;
	element = new int * [row_size];
	for (int i = 0; i < row_size; i++) {
		element[i] = new int[col_size];
	}
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			element[i][j] = m.element[i][j];
		}
	}
}


Matrix::~Matrix() {
	for (int i = 0; i < row_size; i++) {
		delete[] element[i];
	}
	delete[] element;
}


int& Matrix::operator()(int i, int j) const{
	if (i < 1 || i > row_size || j < 1 || j > col_size)
		throw "out of index!";
	return element[i - 1][j - 1];
}


Matrix& Matrix::operator=(const Matrix& m) {
	if (this != &m) {
		for (int i = 0; i < row_size; i++) {
			delete[] element[i];
		}
		delete[] element;
		row_size = m.row_size;
		col_size = m.col_size;
		element = new int * [row_size];
		for (int i = 0; i < row_size; i++) {
			element[i] = new int[col_size];
		}
		for (int i = 0; i < row_size; i++) {
			for (int j = 0; j < col_size; j++) {
				element[i][j] = m.element[i][j];
			}
		}
	}
	return *this;
}


Matrix Matrix::operator+(const Matrix& m) const{
	if (row_size != m.row_size || col_size != m.col_size)
		throw "Dimension not match!";
	Matrix res(row_size, col_size);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			res.element[i][j] = element[i][j] + m.element[i][j];
		}
	}
	return res;
}



Matrix Matrix::operator-(const Matrix& m) const{
	if (row_size != m.row_size || col_size != m.col_size)
		throw "Dimension not match!";
	Matrix res(row_size, col_size);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			res.element[i][j] = element[i][j] - m.element[i][j];
		}
	}
	return res;
}



Matrix Matrix::operator-() {
	Matrix res(row_size, col_size);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			res.element[i][j] = -element[i][j];
		}
	}
	return res;
}


Matrix Matrix::multiply(const Matrix& X, const Matrix& Y) const{
	Matrix res(X.row_size, Y.col_size);
	for (int i = 0; i < X.row_size; i++) {
		for (int j = 0; j < Y.col_size; j++) {
			int val = 0;
			for (int k = 0; k < X.col_size; k++) {
				val += X.element[i][k] * Y.element[k][j];
			}
			res.element[i][j] = val;
		}
	}
	return res;
}

// Strassen

Matrix Matrix::multiply2(const Matrix& X, const Matrix& Y) const{
	if (X.row_size == 1 && X.col_size == 1 && Y.row_size == 1 && Y.col_size == 1) {
		Matrix res(1, 1, X.element[0][0] * Y.element[0][0]);
		return res;
	}

	int X_block_row_size = X.row_size % 2 == 0 ? X.row_size / 2 : X.row_size / 2 + 1;
	int X_block_col_size = X.col_size % 2 == 0 ? X.col_size / 2 : X.col_size / 2 + 1;
	int Y_block_row_size = Y.row_size % 2 == 0 ? Y.row_size / 2 : Y.row_size / 2 + 1;
	int Y_block_col_size = Y.col_size % 2 == 0 ? Y.col_size / 2 : Y.col_size / 2 + 1;
	Matrix A(X_block_row_size, X_block_col_size, 0);
	Matrix B(X_block_row_size, X_block_col_size, 0);
	Matrix C(X_block_row_size, X_block_col_size, 0);
	Matrix D(X_block_row_size, X_block_col_size, 0);
	Matrix E(Y_block_row_size, Y_block_col_size, 0);
	Matrix F(Y_block_row_size, Y_block_col_size, 0);
	Matrix G(Y_block_row_size, Y_block_col_size, 0);
	Matrix H(Y_block_row_size, Y_block_col_size, 0);
	for (int i = 1; i <= X.row_size; ++i) {
		for (int j = 1; j <= X.col_size; ++j) {
			if (i <= X_block_row_size && j <= X_block_col_size) A.element[i - 1][j - 1] = X.element[i - 1][j - 1];
			else if (i <= X_block_row_size && j > X_block_col_size) B.element[i - 1][j - X_block_col_size - 1] = X.element[i - 1][j - 1];
			else if (i > X_block_row_size && j <= X_block_col_size) C.element[i - X_block_row_size - 1][j - 1] = X.element[i - 1][j - 1];
			else D.element[i - X_block_row_size - 1][j - X_block_col_size - 1] = X.element[i - 1][j - 1];
		}
	}
	for (int i = 1; i <= Y.row_size; ++i) {
		for (int j = 1; j <= Y.col_size; ++j) {
			if (i <= Y_block_row_size && j <= Y_block_col_size) E.element[i - 1][j - 1] = Y.element[i - 1][j - 1];
			else if (i <= Y_block_row_size && j > Y_block_col_size) F.element[i - 1][j - Y_block_col_size - 1] = Y.element[i - 1][j - 1];
			else if (i > Y_block_row_size && j <= Y_block_col_size) G.element[i - Y_block_row_size - 1][j - 1] = Y.element[i - 1][j - 1];
			else H.element[i - Y_block_row_size - 1][j - Y_block_col_size - 1] = Y.element[i - 1][j - 1];
		}
	}

	Matrix P1 = multiply2(A, F - H);
	Matrix P2 = multiply2(A + B, H);
	Matrix P3 = multiply2(C + D, E);
	Matrix P4 = multiply2(D, G - E);
	Matrix P5 = multiply2(A + D, E + H);
	Matrix P6 = multiply2(B - D, G + H);
	Matrix P7 = multiply2(A - C, E + F);
	Matrix XY1 = P5 + P4 - P2 + P6;
	Matrix XY2 = P1 + P2;
	Matrix XY3 = P3 + P4;
	Matrix XY4 = P1 + P5 - P3 - P7;
	Matrix res(X.row_size, Y.col_size);
	for (int i = 1; i <= X.row_size; ++i) {
		for (int j = 1; j <= Y.col_size; ++j) {
			if (i <= X_block_row_size && j <= Y_block_col_size) res.element[i - 1][j - 1] = XY1.element[i - 1][j - 1];
			else if (i <= X_block_row_size && j > Y_block_col_size) res.element[i - 1][j - 1] = XY2.element[i - 1][j - Y_block_col_size - 1];
			else if (i > X_block_row_size && j <= Y_block_col_size) res.element[i - 1][j - 1] = XY3.element[i - X_block_row_size - 1][j - 1];
			else res.element[i - 1][j - 1] = XY4.element[i - X_block_row_size - 1][j - Y_block_col_size - 1];
		}
	}
	return res;
}


Matrix Matrix::operator*(const Matrix& m) const{
	return multiply2(*this, m);
}


Matrix Matrix::operator*(int val) const{
	Matrix res(row_size, col_size);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			res.element[i][j] = val * element[i][j];
		}
	}
	return res;
}


Matrix Matrix::operator/(int val) const{
	if (val == 0) {
		throw "divisor 0";
	}
	Matrix res(row_size, col_size);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			res.element[i][j] = element[i][j] / val;
		}
	}
	return res;
}


Matrix Matrix::transpose() const{
	Matrix res(col_size, row_size);
	for (int i = 0; i < col_size; i++) {
		for (int j = 0; j < row_size; j++) {
			res.element[i][j] = element[j][i];
		}
	}
	return res;
}


pair<Matrix, Matrix> Matrix::LU_factorization() const{
	Matrix L(row_size, col_size, 0);
	Matrix U(row_size, col_size, 0);
	for (int i = 0; i < row_size; i++) {
		for (int j = i; j < col_size; j++) {
			int sum = 0;
			for (int k = 0; k < i; k++) {
				sum += L.element[i][k] * U.element[k][j];
			}
			U.element[i][j] = element[i][j] - sum;

		}

		for (int j = i + 1; j < row_size; j++) {
			int sum = 0;
			for (int k = 0; k < i; k++) {
				sum += L.element[j][k] * U.element[k][i];
			}
			L.element[j][i] = (element[j][i] - sum) / U.element[i][i];
		}
		L.element[i][i] = 1;
	}
	return make_pair(L, U);
}


Matrix Matrix::inverse() const{
	pair<Matrix, Matrix> res = this->LU_factorization();
	Matrix L = res.first;
	Matrix U = res.second;
	Matrix inversedL(row_size, col_size, 0);
	Matrix inversedU(row_size, col_size, 0);
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
				int sum = 0;
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
				int sum = 0;
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


ostream& operator<<(ostream& out, const Matrix& m) {
	for (int i = 0; i < m.row_size; i++)
	{
		for (int j = 0; j < m.col_size; j++)
			out << m.element[i][j] << " ";
		out << endl;
	}
	return out;
}