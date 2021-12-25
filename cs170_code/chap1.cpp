#include <iostream>
#include "chap1.h"

int modmul(int x, int y, int N) {
	if (y == 0) return 0;
	int yy = modmul(x, y / 2, N);
	if (y % 2 == 0) return (2 * (yy % N)) % N;
	else return (x % N + (2 * (yy % N)) % N) % N;
}

int modexp(int x, int y, int N) {
	if (y == 0) return 1;
	int z = modexp(x, y / 2, N);
	if (y % 2 == 0) return modmul(z, z, N);
	else return modmul(x, modexp(x, y - 1, N), N);
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
	return inverse_b < 0 ? (a * inverse_b) % N + N : (a * inverse_b) % N; // 0 if inverse not exist, wrap around to 0~N-1
}

bool primality(int N) {
	if (N == 1) return false;
	int a = rand() % (N - 1) + 1;
	if (modexp(a, N - 1, N) == 1) return true;
	else return false;
}

// k=100
bool primality2(int N) {
	if (N == 1) return false;
	for (int i = 0; i < 100; ++i) {
		int a = rand() % (N-1) + 1;
		if (modexp(a, N - 1, N) != 1) return false;
	}
	return true;
}


int gen_random_prime(int lb, int ub) {
	int N = rand() % (ub - 1) + lb;
	while(!primality2(N)) N = rand() % (ub - 1) + lb;
	return N;
}