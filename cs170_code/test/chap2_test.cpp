#include <iostream>
#include <time.h>
#include "../include/binary.h"
#include "../include/matrix.h"
#include "../include/chap2.h"

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