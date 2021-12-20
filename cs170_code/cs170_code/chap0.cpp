#include <iostream>
#include "chap0.h"
#include "lib/matrix.h"

int fib1(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	return fib1(n - 1) + fib1(n - 2);
}

int fib2(int n) {
	if (n == 0) return 0;
	int f0 = 0;
	int f1 = 1;
	int tmp;
	for (int i = 1; i < n; ++i) {
		tmp = f1;
		f1 = f1 + f0;
		f0 = tmp;
	}
	return f1;
}



Matrix<int> matrix_pow(Matrix<int>& m, int n) {
	if (n == 1) return m;
	Matrix<int> res = matrix_pow(m, n / 2);
	if (n % 2 == 1) return m * res * res;
	return res * res;
}

int fib3(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	Matrix<int> m = Matrix<int>(2, 2);
	m(1, 1) = 0;
	m(1, 2) = 1;
	m(2, 1) = 1;
	m(2, 2) = 1;
	m = matrix_pow(m, n);
	return m(1, 2);
}

