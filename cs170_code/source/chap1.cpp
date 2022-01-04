#include <iostream>
#include "../include/chap1.h"

int modmul(int x, int y, int N) {
	if (y == 0) return 0;
	int yy = modmul(x % N, y / 2, N);
	if (y % 2 == 0) return (2 * (yy % N)) % N;
	else return (x % N + (2 * (yy % N)) % N) % N;
}

// N < (2^31 - 1) / 2
int modexp(int x, int y, int N) {
	if (y == 0) return 1;
	int z = modexp(x % N, y / 2, N);
	if (y % 2 == 0) return modmul(z, z, N);
	else return modmul(x % N, modexp(x % N, y - 1, N), N);
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
	// pick a positive integer < N at random
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

// Miller-Rabin
bool primality3(int N) {
	if (N == 1) return false;
	for (int i = 0; i < 50; ++i) {
		int a = rand() % (N - 1) + 1;

		int t = 0;
		int u = N - 1;
		while (u % 2 == 0) {
			u /= 2;
			t++;
		}

		int prev = -1;
		int curr = modexp(a, u, N);
		int val = 0;
		for (int i = 0; i < t; ++i) {
			prev = curr;
			curr = modexp(curr, 2, N);
			if (curr == 1 && prev == -1) val = prev;
		}

		if (curr != 1) return false;
		else {
			if (val == N - 1) return false;
		}

	}
	return true;
}


int gen_random_prime(int lb, int ub) {
	int N = rand() % (ub - lb) + lb;
	while(!primality3(N)) N = rand() % (ub - lb) + lb;
	return N;
}

int naive_AES_encode(int x, int r) {
	return x ^ r;
}

int naive_AES_decode(int y, int r) {
	return y ^ r;
}

pair<int, int> gen_public_key(int p, int q) {
	int N = p * q;
	int e = 3;
	return make_pair(N, e);
}

int gen_private_key(int e, int p, int q) {
	int d = get_multiplicative_inverse(e, (p - 1) * (q - 1));
	return d < 0 ? d + (p - 1) * (q - 1) : d;
}

// x < N
int naive_RSA_encode(int x, int N, int e) {
	return modexp(x, e, N);
}

int naive_RSA_decode(int y, int N, int d) {
	return modexp(y, d, N);
}