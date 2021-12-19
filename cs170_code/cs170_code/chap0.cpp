#include <iostream>
#include "chap0.h"

int fib1(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	return fib1(n - 1) + fib1(n - 2);
}

int fib2(int n) {
	if (n == 0) return 0;
	int f0 = 0;
	int f1 = 1;
	int tmp;
	for (int i = 1; i < n; ++i) {
		tmp = f1;
		f1 = f1 + f0;
		f0 = tmp;
	}
	return f1;
}

