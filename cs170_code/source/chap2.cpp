#include <iostream>
#include "../include/chap2.h"

using namespace std;

void merge(int* a, int l, int m, int r) {
	int* left = new int[m-l];
	int* right = new int[r-m];
	for (int i = l; i < m; ++i) left[i - l] = a[i];
	for (int i = m; i < r; ++i) right[i - m] = a[i];
	int i = 0;
	int j = 0;
	int k = l;
	while (i < m - l && j < r - m) {
		if (left[i] <= right[j]) a[k++] = left[i++];
		else a[k++] = right[j++];
	}
	while (i < m - l) a[k++] = left[i++];
	while (j < m - l) a[k++] = right[j++];
}

void mergesort(int* a, int l, int r) {
	if (r - l <= 1) return;
	int m = l + (r - l) / 2;
	mergesort(a, l, m);
	mergesort(a, m, r);
	merge(a, l, m, r);
}

void swap(int* a, int i, int j) {
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

int partition(int* a, int l, int r) {
	int p = a[r - 1];
	int i = l - 1;
	for (int j = l; j < r - 1; ++j) {
		if (a[j] <= p) {
			i++;
			swap(a, i, j);
		}
	}
	swap(a, i + 1, r - 1);
	return i + 1;
}

int randomized_partition(int* a, int l, int r) {
	int m = rand() % (r - l) + l;
	swap(a, m, r - 1);
	return partition(a, l, r);
}

void quicksort(int* a, int l, int r) {
	if (r - l >= 2) {
		int m = partition(a, l, r);
		quicksort(a, l, m);
		quicksort(a, m + 1, r);
	}
}

void randomized_quicksort(int* a, int l, int r) {
	if (r - l >= 2) {
		int m = randomized_partition(a, l, r);
		randomized_quicksort(a, l, m);
		randomized_quicksort(a, m + 1, r);
	}
}

pair<int, int> split(int* a, int l, int r, int val) {
	int k = l;
	for (int i = l; i < r; ++i) {
		if (a[i] < val) {
			swap(a, k, i);
			k++;
		}
	}
	int lb = k;
	for (int i = k; i < r; ++i) {
		if (a[i] == val) {
			swap(a, k, i);
			k++;
		}
	}
	int ub = k;
	return make_pair(lb, ub);
}

// k'th smallest element
int select(int* a, int l, int r, int k) {
	int val = a[rand() % (r - l) + l];
	pair<int, int> res = split(a, l, r, val);
	int lb = res.first; int ub = res.second;
	if (k <= lb - l) return select(a, l, lb, k);
	else if (k > ub - l) return select(a, ub, r, k - ub + l);
	else return val;
}