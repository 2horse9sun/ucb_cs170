#include <iostream>
#include <time.h>
#include "../lib/binary.h"
#include "../chap1.h"

void addition_test() {
    std::cout << "addition_test" << std::endl;
    std::cout << "Input the first binary integer a: ";
    Binary a = Binary();
    std::cin >> a;
    std::cout << "Decimal value of a: " << a.get_value() << endl;
    std::cout << "Input the second binary integer b: ";
    Binary b = Binary();
    std::cin >> b;
    std::cout << "Decimal value of b: " << b.get_value() << endl;
    clock_t start, end;
    start = clock();

    Binary c = a + b;
    std::cout << "Output: " << c << std::endl;

    end = clock();
    std::cout << "Decimal output: " << c.get_value() << std::endl;
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void subtraction_test() {
    std::cout << "subtraction_test" << std::endl;
    std::cout << "Input the first binary integer a: ";
    Binary a = Binary();
    std::cin >> a;
    std::cout << "Decimal value of a: " << a.get_value() << endl;
    std::cout << "Input the second binary integer b: ";
    Binary b = Binary();
    std::cin >> b;
    std::cout << "Decimal value of b: " << b.get_value() << endl;
    clock_t start, end;
    start = clock();

    Binary c = a - b;
    std::cout << "Output: " << c << std::endl;

    end = clock();
    std::cout << "Decimal output: " << c.get_value() << std::endl;
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void multiplication_test() {
    std::cout << "multiplication_test" << std::endl;
    std::cout << "Input the first binary integer a: ";
    Binary a = Binary();
    std::cin >> a;
    std::cout << "Decimal value of a: " << a.get_value() << endl;
    std::cout << "Input the second binary integer b: ";
    Binary b = Binary();
    std::cin >> b;
    std::cout << "Decimal value of b: " << b.get_value() << endl;
    clock_t start, end;
    start = clock();

    Binary c = a * b;
    std::cout << "Output: " << c << std::endl;

    end = clock();
    std::cout << "Decimal output: " << c.get_value() << std::endl;
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void division_test() {
    std::cout << "division_test_test" << std::endl;
    std::cout << "Input the first binary integer a: ";
    Binary a = Binary();
    std::cin >> a;
    std::cout << "Decimal value of a: " << a.get_value() << endl;
    std::cout << "Input the second binary integer b: ";
    Binary b = Binary();
    std::cin >> b;
    std::cout << "Decimal value of b: " << b.get_value() << endl;
    clock_t start, end;
    start = clock();

    pair<Binary, Binary> res = a / b;
    std::cout << "Output: (" << res.first << ", " << res.second << ")" << std::endl;

    end = clock();
    std::cout << "Decimal output: (" << res.first.get_value() << ", " << res.second.get_value() << ")" << std::endl;
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}