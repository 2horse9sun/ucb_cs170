#ifndef matrix_
#define matrix_
#include<iostream>
using namespace std;

template<class T>
class Matrix {
public:
	T** element;
	int rowNum;
	int colNum;

	Matrix() {}

	Matrix(int rowNum, int colNum) {
		if (rowNum < 0 || colNum < 0)
			throw "rowNum and colNum are positive!";
		if ((rowNum == 0 || colNum == 0) && (rowNum != 0 || colNum != 0))
			throw "Invalid params!";
		this->rowNum = rowNum;
		this->colNum = colNum;
		element = new T * [rowNum];
		for (int i = 0; i < rowNum; i++) {
			element[i] = new T[colNum];
		}
	}

	Matrix(int rowNum, int colNum, T val) {
		if (rowNum < 0 || colNum < 0)
			throw "rowNum and colNum are positive!";
		if ((rowNum == 0 || colNum == 0) && (rowNum != 0 || colNum != 0))
			throw "Invalid params!";
		this->rowNum = rowNum;
		this->colNum = colNum;
		element = new T * [rowNum];
		for (int i = 0; i < rowNum; i++) {
			element[i] = new T[colNum];
		}
		for (int i = 0; i < rowNum; i++) {
			for (int j = 0; j < colNum; j++) {
				element[i][j] = 0;
			}
		}
	}


	Matrix(const Matrix<T>& m) {
		rowNum = m.rowNum;
		colNum = m.colNum;
		element = new T * [rowNum];
		for (int i = 0; i < rowNum; i++) {
			element[i] = new T[colNum];
		}
		for (int i = 0; i < rowNum; i++) {
			for (int j = 0; j < colNum; j++) {
				element[i][j] = m.element[i][j];
			}
		}
	}

	~Matrix() {
		for (int i = 0; i < rowNum; i++) {
			delete[] element[i];
		}
		delete[] element;
	}

	T& operator()(int i, int j) {
		if (i < 1 || i > rowNum|| j < 1 || j > colNum)
			throw "out of index!";
		return element[i - 1][j - 1];
	}

	Matrix<T>& operator=(const Matrix<T>& m) {
		if (this != &m) {
			for (int i = 0; i < rowNum; i++) {
				delete[] element[i];
			}
			delete[] element;
			rowNum = m.rowNum;
			colNum = m.colNum;
			element = new T * [rowNum];
			for (int i = 0; i < rowNum; i++) {
				element[i] = new T[colNum];
			}
			for (int i = 0; i < rowNum; i++) {
				for (int j = 0; j < colNum; j++) {
					element[i][j] = m.element[i][j];
				}
			}
		}
		return *this;
	}

	Matrix<T> operator+(const Matrix<T>& m) {
		if (rowNum != m.rowNum || colNum != m.colNum)
			throw "Dimension not match!";
		Matrix<T> res(rowNum, colNum);
		for (int i = 0; i < rowNum; i++) {
			for (int j = 0; j < colNum; j++) {
				res.element[i][j] = element[i][j] + m.element[i][j];
			}
		}
		return res;
	}

	Matrix<T> operator-(const Matrix<T>& m) {
		if (rowNum != m.rowNum || colNum != m.colNum)
			throw "Dimension not match!";
		Matrix<T> res(rowNum, colNum);
		for (int i = 0; i < rowNum; i++) {
			for (int j = 0; j < colNum; j++) {
				res.element[i][j] = element[i][j] - m.element[i][j];
			}
		}
		return res;
	}

	Matrix<T> operator-() {
		Matrix<T> res(rowNum, colNum);
		for (int i = 0; i < rowNum; i++) {
			for (int j = 0; j < colNum; j++) {
				res.element[i][j] = -element[i][j];
			}
		}
		return res;
	}

	Matrix<T> operator*(const Matrix<T>& m) {
		if (colNum != m.rowNum)
			throw "Dimension not match!";
		Matrix<T> res(rowNum, m.colNum);
		for (int i = 0; i < rowNum; i++) {
			for (int j = 0; j < m.colNum; j++) {
				T val = 0;
				for (int k = 0; k < colNum; k++) {
					val += element[i][k] * m.element[k][j];
				}
				res.element[i][j] = val;
			}
		}
		return res;
	}

	Matrix<T> operator*(T val) {
		Matrix<T> res(rowNum, colNum);
		for (int i = 0; i < rowNum; i++) {
			for (int j = 0; j < colNum; j++) {
				res.element[i][j] = val * element[i][j];
			}
		}
		return res;
	}

	Matrix<T> operator/(T val) {
		if (val == 0) {
			throw "divisor 0";
		}
		Matrix<T> res(rowNum, colNum);
		for (int i = 0; i < rowNum; i++) {
			for (int j = 0; j < colNum; j++) {
				res.element[i][j] = element[i][j] / val;
			}
		}
		return res;
	}

	Matrix<T> transpose() {
		Matrix<T> res(colNum, rowNum);
		for (int i = 0; i < colNum; i++) {
			for (int j = 0; j < rowNum; j++) {
				res.element[i][j] = element[j][i];
			}
		}
		return res;
	}


	pair<Matrix<T>, Matrix<T>> LU_factorization() {
		Matrix<T> L(rowNum, colNum, 0);
		Matrix<T> U(rowNum, colNum, 0);
		for (int i = 0; i < rowNum; i++) {
			for (int j = i; j < colNum; j++) {
				T sum = 0;
				for (int k = 0; k < i; k++) {
					sum += L.element[i][k] * U.element[k][j];
				}
				U.element[i][j] = element[i][j] - sum;

			}

			for (int j = i + 1; j < rowNum; j++) {
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
		Matrix<T> inversedL(rowNum, colNum, 0);
		Matrix<T> inversedU(rowNum, colNum, 0);
		for (int i = 0; i < colNum; i++) {
			for (int j = 0; j < rowNum; j++) {
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
		for (int p = 0; p < colNum; p++) {
			for (int i = 0; i < rowNum - p; i++) {
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
};

template<class T>
ostream& operator<<(ostream& out, const Matrix<T>& m) {
	for (int i = 0; i < m.rowNum; i++)
	{
		for (int j = 0; j < m.colNum; j++)
			out << m.element[i][j] << " ";
		out << endl;
	}
	return out;
}

#endif
