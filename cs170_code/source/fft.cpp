#include <iostream>
#include <cmath>
#include <math.h>
#include "../include/complex.h"
#include "../include/constant.h"
#include "../include/fft.h"

using namespace std;


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
Complex* do_FFT(Complex* a, int n, double inverse) {
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
	Complex* y_e = do_FFT(a_e, n / 2, inverse);
	Complex* y_o = do_FFT(a_o, n / 2, inverse);

	for (int i = 0; i < n / 2; ++i) {
		y[i] = y_e[i] + w * y_o[i];
		y[i + n / 2] = y_e[i] - w * y_o[i];
		w = w * w_n;
	}
	return y;
}

Complex* FFT(Complex* a, int n) {
	if (n == 1) return a;
	Complex* y = do_FFT(a, n, -1);
	return y;
}


Complex* IFFT(Complex* y, int n) {
	if (n == 1) return y;
	Complex* a = do_FFT(y, n, 1);
	for (int i = 0; i < n; ++i) a[i] = a[i] / (double)n;
	return a;
}