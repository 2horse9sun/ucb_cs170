#include <iostream>
#include "chap1.h"

int modexp(int x, int y, int N) {
	if (y == 0) return 1;
	int z = modexp(x, y / 2, N);
	if (y % 2 == 0) return (z * z) % N;
	else return (x * z * z) % N;
}

int euclid(int a, int b) {
	if (b == 0) return a;
	return euclid(b, a % b);
}


// ax + by = d
// pseudocode:
//   if b=0: return (1, 0, a)
//   (x', y', d) = extended_euclid(b, a mod b)
//   return (y' x'-(a/b)y', d)
void extended_euclid(int& x, int& y, int& d, int a, int b) {
	if (b == 0) {
		x = 1; y = 0; d = a;
		return;
	}
	int xx; int yy;
	extended_euclid(xx, yy, d, b, a % b);
	x = yy;
	y = xx - (a / b) * yy;
}

// by extended_euclid
int get_multiplicative_inverse(int a, int N) {
	int x; int y; int d;
	extended_euclid(x, y, d, a, N);
	if (d != 1) return 0; // inverse not exist
	return x;
}

int mod_divide(int a, int b, int N) {
	int inverse_b = get_multiplicative_inverse(b, N);
	return inverse_b < 0 ? (a * inverse_b) % N + N : (a * inverse_b) % N; // 0 if inverse not exist
}