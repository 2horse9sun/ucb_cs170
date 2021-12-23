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
    std::cout << "division_test" << std::endl;
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

    Binary res = a / b;
    std::cout << "Output: " << res << std::endl;

    end = clock();
    std::cout << "Decimal output: " << res.get_value() << std::endl;
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void modulo_test() {
    std::cout << "modulo_test" << std::endl;
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

    Binary res = a % b;
    std::cout << "Output: " << res << std::endl;

    end = clock();
    std::cout << "Decimal output: " << res.get_value() << std::endl;
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}


void modexp_test() {
    std::cout << "modexp_test (N = 1337)" << std::endl;
    std::cout << "Input integer x: ";
    int x;
    std::cin >> x;
    std::cout << "Input integer y: ";
    int y;
    std::cin >> y;
    clock_t start, end;
    start = clock();

    std::cout << "Output: " << modexp(x, y, 1337) << std::endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void euclid_test() {
    std::cout << "euclid_test" << std::endl;
    std::cout << "Input the first integer a: ";
    int a;
    std::cin >> a;
    std::cout << "Input the second integer b: ";
    int b;
    std::cin >> b;
    clock_t start, end;
    start = clock();

    int gcd = euclid(a, b);
    std::cout << "gcd of a and b is: " << gcd << std::endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void extended_euclid_test() {
    std::cout << "extended_euclid_test" << std::endl;
    std::cout << "Input the first integer a: ";
    int a;
    std::cin >> a;
    std::cout << "Input the second integer b: ";
    int b;
    std::cin >> b;
    clock_t start, end;
    start = clock();

    int x; int y; int d;
    extended_euclid(x, y, d, a, b);
    std::cout << "(x, y, d): " << "(" << x << ", " << y << ", " << d << ")" << std::endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void mod_divide_test() {
    std::cout << "mod_divide_test (N = 1337)" << std::endl;
    std::cout << "Input the first integer a: ";
    int a;
    std::cin >> a;
    std::cout << "Input the second integer b: ";
    int b;
    std::cin >> b;
    clock_t start, end;
    start = clock();

    std::cout << "Output: " << mod_divide(a, b, 1337) << std::endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}