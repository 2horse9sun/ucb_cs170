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
    std::cout << "modexp_test (N = 1000000007)" << std::endl;
    std::cout << "Input integer x: ";
    int x;
    std::cin >> x;
    std::cout << "Input integer y: ";
    int y;
    std::cin >> y;
    clock_t start, end;
    start = clock();

    std::cout << "Output: " << modexp(x, y, 1000000007) << std::endl;

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

void primality_test() {
    std::cout << "primality_test" << std::endl;
    std::cout << "Input an integer N: ";
    int N;
    std::cin >> N;
    clock_t start, end;
    start = clock();

    std::cout << "N is prime ? " << (primality(N) ? "Yes" : "No") << std::endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void primality2_test() {
    std::cout << "primality2_test" << std::endl;
    std::cout << "Input an integer N: ";
    int N;
    std::cin >> N;
    clock_t start, end;
    start = clock();

    std::cout << "N is prime ? " << (primality2(N) ? "Yes" : "No") << std::endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void primality3_test() {
    std::cout << "primality3_test" << std::endl;
    std::cout << "Input an integer N: ";
    int N;
    std::cin >> N;
    clock_t start, end;
    start = clock();

    std::cout << "N is prime ? " << (primality3(N) ? "Yes" : "No") << std::endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void gen_random_prime_test() {
    std::cout << "gen_random_prime_test" << std::endl;
    std::cout << "Input the lower bound: ";
    int lb;
    std::cin >> lb;
    std::cout << "Input the upper bound: ";
    int ub;
    std::cin >> ub;
    std::cout << "Input the num of primes: ";
    int N;
    std::cin >> N;
    std::cout << "Primes generated: " << endl;
    clock_t start, end;
    start = clock();
    
    for (int i = 0; i < N; ++i) {
        std::cout << gen_random_prime(lb, ub) << std::endl;
    }
    
    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void naive_AES_test() {
    std::cout << "naive_AES_test" << std::endl;
    std::cout << "Input an integer x as a message: ";
    int x;
    std::cin >> x;
    std::cout << "Input an integer r as private key: ";
    int r;
    std::cin >> r;
    clock_t start, end;
    start = clock();

    int y = naive_AES_encode(x, r);
    std::cout << "Encoded: " << y << std::endl;
    std::cout << "Decoded: " << naive_AES_decode(y, r) << std::endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}

void naive_RSA_test() {
    std::cout << "naive_RSA_test" << std::endl;
    std::cout << "Input an integer x as a message: ";
    int x;
    std::cin >> x;
    clock_t start, end;
    start = clock();

    // p, q should be large enough, here they are small (avoid overflow)
    int p = 10601;
    int q = 19763;
    std::cout << "Pick two large random primes: " << "(" << p << ", " << q << ")" << std::endl;
    pair<int, int> public_key = gen_public_key(p, q);
    int N = public_key.first;
    int e = public_key.second;
    std::cout << "Public key: " << "(" << N << ", " << e << ")" << std::endl;
    int d = gen_private_key(e, p, q);
    std::cout << "Private key: " << d << std::endl;

    int y = naive_RSA_encode(x, N, e);
    std::cout << "Encoded: " << y << std::endl;
    std::cout << "Decoded: " << naive_RSA_decode(y, N, d) << std::endl;

    end = clock();
    std::cout << "time = " << (double(end - start) / CLOCKS_PER_SEC) * 1000 << "ms" << std::endl;
    std::cout << "======================================" << std::endl;
}