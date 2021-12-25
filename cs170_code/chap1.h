#pragma once
#include <iostream>

void addition_test();
void subtraction_test();
void multiplication_test();
void division_test();
void modulo_test();

int modexp(int x, int y, int N);
void modexp_test();

// gcd
int euclid(int a, int b);
void euclid_test();
void extended_euclid(int& x, int& y, int& d, int a, int b);
void extended_euclid_test();

int get_multiplicative_inverse(int a, int N);
int mod_divide(int a, int b, int N);
void mod_divide_test();

bool primality(int N);
void primality_test();
bool primality2(int N);
void primality2_test();
int gen_random_prime(int lb, int ub);
void gen_random_prime_test();