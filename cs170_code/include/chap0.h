#pragma once
#ifndef chap0_
#define chap0_

#include <iostream>
#include "./matrix.h"
using namespace std;
// Fibonacci, exponential
int fib1(int n);
void fib1_test();

// Fibonacci, polynomial
int fib2(int n);
void fib2_test();

// Fibonacci, using matrix
Matrix matrix_pow(Matrix& m, int n);
int fib3(int n);
void fib3_test();

#endif // !chap0_

