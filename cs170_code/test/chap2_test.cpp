#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include "../include/binary.h"
#include "../include/complex.h"
#include "../include/matrix.h"
#include "../include/chap2.h"

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
    input[len] = Complex(num);
    len++;
    while (cin.get() != '\n') {
        cin >> num;
        input[len] = Complex(num);
        len++;
    }
    clock_t start, end;
    start = clock();

    int n = find_nearest_two_pow(len);
    Complex* a = new Complex[n];
    for (int i = 0; i < n; ++i) a[i] = i < len ? input[i] : Complex(0);
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