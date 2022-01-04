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
	return;
}

void mergesort(int* a, int l, int r) {
	if (r - l <= 1) return;
	int m = l + (r - l) / 2;
	mergesort(a, l, m);
	mergesort(a, m, r);
	merge(a, l, m, r);
	return;
}