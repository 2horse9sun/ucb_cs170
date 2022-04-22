#include <iostream>
#include <cmath>
#include <math.h>
#include "../include/complex.h"
#include "../include/global.h"
#include "../include/fft.h"

using namespace std;

int bit_reverse_table_0[1] = {0};
int bit_reverse_table_1[2] = {0, 1};
int bit_reverse_table_2[4] = { 0, 2, 1, 3 };
int bit_reverse_table_3[8] = { 0, 4, 2, 6, 1, 5, 3, 7 };
int bit_reverse_table_4[16] = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };
int bit_reverse_table_5[32] = { 0, 16, 8, 24, 4, 20, 12, 28, 2, 18, 10, 26, 6, 22, 14, 30, 1, 17, 9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, 15, 31 };
int* bit_reverse_table[6] = { bit_reverse_table_0,
							  bit_reverse_table_1,
							  bit_reverse_table_2,
							  bit_reverse_table_3,
							  bit_reverse_table_4,
							  bit_reverse_table_5};



int find_nearest_two_pow(int len) {
	for (int i = 1; ; ++i) {
		int power = (int)pow(2, i);
		if (power >= len) {
			return power;
		}
	}
}


// n is power of 2, if not, add zeros
// n-point DFT
Complex* do_recursive_FFT(Complex* a, int n, double inverse) {
	if (n == 1) return a;
	Complex w_n(cos(inverse * 2 * PI / n), sin(inverse * 2 * PI / n));
	Complex w(1.0, 0.0);
	Complex* a_e = new Complex[n / 2];
	Complex* a_o = new Complex[n / 2];
	Complex* y = new Complex[n];

	for (int i = 0; i < n; ++i) {
		if (i % 2 == 0) a_e[i / 2] = a[i];
		else a_o[i / 2] = a[i];
	}
	Complex* y_e = do_recursive_FFT(a_e, n / 2, inverse);
	Complex* y_o = do_recursive_FFT(a_o, n / 2, inverse);

	for (int i = 0; i < n / 2; ++i) {
		y[i] = y_e[i] + w * y_o[i];
		y[i + n / 2] = y_e[i] - w * y_o[i];
		w = w * w_n;
	}
	return y;
}


// 2,4,8,16,32-bit only, expand as needed
int rev(int k, int n) {
	int power = (int)log2(n);
	return bit_reverse_table[power][k];
}

Complex* bit_reverse(Complex* a, int n) {
	Complex* A = new Complex[n];
	for (int i = 0; i < n; ++i) A[rev(i, n)] = a[i];
	return A;
}

// n is power of 2, if not, add zeros
// n-point DFT
Complex* do_iterative_FFT(Complex* a, int n, double inverse) {
	Complex* A = bit_reverse(a, n);

	// level
	for (int s = 1; s <= (int)log2(n); ++s) {
		int m = (int)pow(2, s);
		Complex w_m(cos(inverse * 2 * PI / m), sin(inverse * 2 * PI / m));

		// combine A[k : k+2^(s-1)) and A[k+2^(s-1) : k+2^s) into A[k : k+2^s)
		for (int k = 0; k < n; k += m) {
			Complex w(1.0, 0.0);
			for (int j = 0; j < m / 2; ++j) {
				Complex u = A[k + j]; // y_e[j]
				Complex t = w * A[k + m / 2 + j]; // w*y_o[j]
				A[k + j] = u + t;
				A[k + m / 2 + j] = u - t;
				w = w * w_m;
			}
		}
	}
	return A;
}

Complex* FFT(Complex* a, int n) {
	if (n == 1) return a;
	Complex* y = do_iterative_FFT(a, n, -1);
	return y;
}


Complex* IFFT(Complex* y, int n) {
	if (n == 1) return y;
	Complex* a = do_iterative_FFT(y, n, 1);
	for (int i = 0; i < n; ++i) a[i] = a[i] / (double)n;
	return a;
}