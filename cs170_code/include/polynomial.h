#ifndef polynomial_
#define polynomial_
#include<iostream>
#include<math.h>
#include<cmath>
#include "../include/constant.h"
#include "../include/complex.h"
#include "../include/fft.h"
using namespace std;

class Polynomial {
public:
	// coefficients: a[0] + a[1]x + a[2]x^2 + ... + a[len-1]x^(len-1)
	double* a;
	// degree = len - 1
	int len;

	
	Polynomial(double* input, int input_len) {
		len = input_len;
		a = new double[len];
		for (int i = 0; i < len; ++i) {
			a[i] = input[i];
		}
		for (int i = len-1; i > 0; ++i) {
			if (a[i] == 0) len--;
			else break;
		}
	}

	Polynomial(const Polynomial& p) {
		len = p.len;
		a = new double[len];
		for (int i = 0; i < len; ++i) {
			a[i] = p.a[i];
		}
	}

	~Polynomial() {
		delete[] a;
	}

	double get_value(double x) {
		double val = 0;
		for (int i = 0; i < len; ++i) {
			val += a[0] * pow(x, i);
		}
		return val;
	}

	Polynomial& operator=(const Polynomial& p) {
		if (this != &p) {
			delete[] a;

			len = p.len;
			a = new double[len];
			for (int i = 0; i < len; ++i) {
				a[i] = p.a[i];
			}
		}
		return *this;
	}

	bool operator==(const Polynomial& p) {
		if (len != p.len) return false;
		for (int i = 0; i < len; ++i) {
			if (a[i] != p.a[i]) return false;
		}
		return true;
	}

	Polynomial operator+(const Polynomial& p) {
		int sum_len = max(len, p.len);
		double* sum = new double[sum_len];
		for (int i = 0; i < sum_len; ++i) {
			sum[i] = (i < len ? a[i] : 0) + (i < p.len ? p.a[i] : 0);
		}
		for (int i = sum_len - 1; i > 0; ++i) {
			if (sum[i] == 0) sum_len--;
			else break;
		}
		return Polynomial(sum, sum_len);
	}

	friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2) {
		return p1 + p2;
	}

	Polynomial operator-(const Polynomial& p) {
		int subtraction_len = max(len, p.len);
		double* subtraction = new double[subtraction_len];
		for (int i = 0; i < subtraction_len; ++i) {
			subtraction[i] = (i < len ? a[i] : 0) - (i < p.len ? p.a[i] : 0);
		}
		for (int i = subtraction_len - 1; i > 0; ++i) {
			if (subtraction[i] == 0) subtraction_len--;
			else break;
		}
		return Polynomial(subtraction, subtraction_len);
	}

	friend Polynomial operator-(const Polynomial& p1, const Polynomial& p2) {
		return p1 - p2;
	}

	Polynomial multiplication_FFT(const Polynomial& p1, const Polynomial& p2) {
		int max_len = max(p1.len, p2.len);
		int n = find_nearest_two_pow(max_len);
		Complex* A = new Complex[2 * n];
		Complex* B = new Complex[2 * n];
		for (int i = 0; i < 2 * n; ++i) {
			A[i] = i < p1.len ? p1.a[i] : 0;
			B[i] = i < p2.len ? p2.a[i] : 0;
		}

		// FFT
		Complex* A_FFT = FFT(A, 2 * n);
		Complex* B_FFT = FFT(B, 2 * n);
		Complex* product_FFT = new Complex[2 * n];
		// point2point multiply
		for (int i = 0; i < 2 * n; ++i) {
			product_FFT[i] = A_FFT[i] * B_FFT[i];
		}
		// IFFT
		Complex* product_IFFT = IFFT(product_FFT, 2 * n);

		double* product = new double[2 * n];
		int product_len = 2 * n;
		for (int i = 0; i < product_len; ++i) {
			product[i] = (double)product_IFFT[i];
		}
		product_len = p1.len + p2.len;

		delete[] A; delete[] B; delete[] A_FFT; delete[] B_FFT; 
		delete[] product_FFT; delete[] product_IFFT;
		return Polynomial(product, product_len);
	}

	Polynomial operator*(const Polynomial& p) {
		return multiplication_FFT(*this, p);
	}


	friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2) {
		return p1 * p2;
	}


	friend ostream& operator<<(ostream& out, const Polynomial& p) {
		for (int i = 0; i < p.len; ++i) {
			out << p.a[i] << " ";
		}
		out << endl;
		return out;
	}

};




#endif
