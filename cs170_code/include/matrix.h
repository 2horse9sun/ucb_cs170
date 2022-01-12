#ifndef matrix_
#define matrix_
#include<iostream>
using namespace std;

class Matrix {
public:
	int** element;
	int row_size;
	int col_size;

	Matrix() {}

	Matrix(int row_size, int col_size);

	Matrix(int row_size, int col_size, int val);


	Matrix(const Matrix& m);

	~Matrix();

	int& operator()(int i, int j) const;
	Matrix& operator=(const Matrix& m);
	Matrix operator+(const Matrix& m) const;
	Matrix operator-(const Matrix& m) const;
	Matrix operator-();

	Matrix multiply(const Matrix& X, const Matrix& Y) const;
	// Strassen
	Matrix multiply2(const Matrix& X, const Matrix& Y) const;
	Matrix operator*(const Matrix& m) const;
	Matrix operator*(int val) const;
	Matrix operator/(int val) const;

	Matrix transpose() const;

	pair<Matrix, Matrix> LU_factorization() const;

	Matrix inverse() const;

	friend ostream& operator<<(ostream& out, const Matrix& m);

};



#endif
