#include <iostream>
#include <time.h>
#include "../chap0.h"

void fib1_test() {
    std::cout << "fib1_test" << std::endl;
    std::cout << "Input n: ";

    int n;
    std::cin >> n;
    clock_t start, end;
    start = clock();

    std::cout << "Output: " << fib1(n) << std::endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void fib2_test() {
    std::cout << "fib2_test" << std::endl;
    std::cout << "Input n: ";

    int n;
    std::cin >> n;
    clock_t start, end;
    start = clock();

    std::cout << "Output: " << fib2(n) << std::endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}