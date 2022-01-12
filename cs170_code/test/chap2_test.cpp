#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include "../include/binary.h"
#include "../include/complex.h"
#include "../include/matrix.h"
#include "../include/fft.h"
#include "../include/polynomial.h"
#include "../include/chap2.h"

void matrix_multiplication_test() {
    Matrix m1(2, 3);
    m1(1, 1) = 1; m1(1, 2) = 4; m1(1, 3) = 2; m1(2, 1) = 6; m1(2, 2) = 1; m1(2, 3) = 3;
    Matrix m2(3, 2);
    m2(1, 1) = 2; m2(1, 2) = 1; m2(2, 1) = 1; m2(2, 2) = 4; m2(3, 1) = 0; m2(3, 2) = 2;
    cout << "Matrix1: " << endl << m1;
    cout << "Matrix2: " << endl << m2;
    cout << "Multiplication: " << endl << m1 * m2;
}

void quicksort_test() {
    std::cout << "quicksort_test" << std::endl;
    std::cout << "Input integers separated by space: ";
    int* a = new int[64];
    int num = 0;
    int len = 0;
    cin >> num;
    a[len] = num;
    len++;
    while (cin.get() != '\n') {
        cin >> num;
        a[len] = num;
        len++;
    }
    clock_t start, end;
    start = clock();

    randomized_quicksort(a, 0, len);
    std::cout << "Sorted: ";
    for (int i = 0; i < len; ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void mergesort_test() {
    std::cout << "mergesort_test" << std::endl;
    std::cout << "Input integers separated by space: ";
    int* a = new int[64];
    int num = 0;
    int len = 0;
    cin >> num;
    a[len] = num;
    len++;
    while (cin.get() != '\n') {
        cin >> num;
        a[len] = num;
        len++;
    }
    clock_t start, end;
    start = clock();

    mergesort(a, 0, len);
    std::cout << "Sorted: ";
    for (int i = 0; i < len; ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void external_mergesort_test() {
    std::cout << "external_mergesort_test" << std::endl;
    std::cout << "Input # of integers: ";
    long size;
    cin >> size;
    string file_name = "c:/users/jsjhf/desktop/tests/test";
    gen_random_int_file(file_name, size);

    clock_t start, end;
    start = clock();

    external_mergesort(file_name);

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}



void select_test() {
    std::cout << "select_test" << std::endl;
    std::cout << "Input integers separated by space: ";
    int* a = new int[64];
    int num = 0;
    int len = 0;
    cin >> num;
    a[len] = num;
    len++;
    while (cin.get() != '\n') {
        cin >> num;
        a[len] = num;
        len++;
    }
    clock_t start, end;
    std::cout << "Input an integer k: ";
    int k;
    cin >> k;
    start = clock();

    std::cout << "k'th smallest element: " << select(a, 0, len, k) << endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}


void FFT_test() {
    std::cout << "FFT_test" << std::endl;
    std::cout << "Input numbers separated by space: ";
    Complex* input = new Complex[64];
    double num = 0;
    int len = 0;
    cin >> num;
    input[len] = Complex(num, 0.0);
    len++;
    while (cin.get() != '\n') {
        cin >> num;
        input[len] = Complex(num, 0.0);
        len++;
    }
    clock_t start, end;
    start = clock();

    int n = find_nearest_two_pow(len);
    Complex* a = new Complex[n];
    for (int i = 0; i < n; ++i) a[i] = i < len ? input[i] : Complex(0.0, 0.0);
    Complex* y = FFT(a, n);
    std::cout << "FFT: " << endl;
    for (int i = 0; i < n; ++i) cout << y[i] << " ";
    cout << endl;
    Complex* aa = IFFT(y, n);
    std::cout << "IFFT: " << endl;
    for (int i = 0; i < n; ++i) cout << aa[i] << " ";
    cout << endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void polynomial_multiplication_test() {
    std::cout << "polynomial_test" << std::endl;
    std::cout << "Input polynomial 1 's coefficients separated by space: ";
    double* a = new double[64];
    double num = 0;
    int a_len = 0;
    cin >> num;
    a[a_len] = num;
    a_len++;
    while (cin.get() != '\n') {
        cin >> num;
        a[a_len] = num;
        a_len++;
    }
    std::cout << "Input polynomial 2 's coefficients separated by space: ";
    double* b = new double[64];
    int b_len = 0;
    cin >> num;
    b[b_len] = num;
    b_len++;
    while (cin.get() != '\n') {
        cin >> num;
        b[b_len] = num;
        b_len++;
    }
    clock_t start, end;
    start = clock();

    Polynomial pa(a, a_len);
    Polynomial pb(b, b_len);
    std::cout << "Sum: " << endl;
    cout << pa + pb << endl;
    std::cout << "Subtraction: " << endl;
    cout << pa - pb << endl;
    std::cout << "Multiplication: " << endl;
    cout << pa * pb << endl;
    cout << endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}