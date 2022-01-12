#pragma once
#ifndef fft_
#define fft_
#include <iostream>
#include "./complex.h"

using namespace std;


int find_nearest_two_pow(int len);
// n is power of 2, if not, add zeros
// n-point DFT
Complex* do_FFT(Complex* a, int n, double inverse);
Complex* FFT(Complex* a, int n);
Complex* IFFT(Complex* y, int n);

#endif