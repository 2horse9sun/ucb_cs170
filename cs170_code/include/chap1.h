#pragma once
#ifndef chap1_
#define chap1_
#include <iostream>

using namespace std;

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
bool primality3(int N);
void primality3_test();
int gen_random_prime(int lb, int ub);
void gen_random_prime_test();

int naive_AES_encode(int x, int r);
int naive_AES_decode(int y, int r);
void naive_AES_test();

pair<int, int> gen_public_key(int p, int q);
int gen_private_key(int e, int p, int q);
int naive_RSA_encode(int x, int N, int e);
int naive_RSA_decode(int y, int N, int d);
void naive_RSA_test();

#endif