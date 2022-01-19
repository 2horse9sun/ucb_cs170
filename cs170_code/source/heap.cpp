#include <iostream>
#include "../include/heap.h"

using namespace std;

int PARENT(int i) {
	return (i + 1) / 2 - 1;
}

int LEFT(int i) {
	return 2 * (i + 1) - 1;
}

int RIGHT(int i) {
	return 2 * (i + 1);
}




void max_heapify(int* a, int l, int r, int i) {
	int largest = a[i];
	int largest_index = i;
	if (LEFT(i) < r && a[i] < a[LEFT(i)]) {
		largest = a[LEFT(i)];
		largest_index = LEFT(i);
	}
	if (RIGHT(i) < r && largest < a[RIGHT(i)]) {
		largest = a[RIGHT(i)];
		largest_index = RIGHT(i);
	}
	if (largest_index != i) {
		swap(a[i], a[largest_index]);
		max_heapify(a, l, r, largest_index);
	}
}

void build_maxheap(int* a, int l, int r) {
	for (int i = PARENT(r - 1); i >= l; --i) max_heapify(a, l, r, i);
}

void max_heapsort(int* a, int l, int r) {
	build_maxheap(a, l, r);
	for (int i = r - 1; i >= l + 1; --i) {
		swap(a[l], a[i]);
		r--;
		max_heapify(a, l, r, l);
	}
}

int maxheap_top(int* a, int l, int r) {
	if (r - l == 0) return INT_MIN;
	return a[l];
}

int maxheap_pop(int* a, int l, int r) {
	if (r - l == 0) return INT_MIN;
	int max_val = a[l];
	a[l] = a[r - 1];
	max_heapify(a, l, r - 1, l);
	return max_val;
}

void maxheap_push(int* a, int l, int r, int key) {
	a[r] = key;
	while (r > 0 && a[PARENT(r)] < a[r]) {
		swap(a[r], a[PARENT(r)]);
		r = PARENT(r);
	}
}






void min_heapify(int* a, int l, int r, int i) {
	int smallest = a[i];
	int smallest_index = i;
	if (LEFT(i) < r && a[i] > a[LEFT(i)]) {
		smallest = a[LEFT(i)];
		smallest_index = LEFT(i);
	}
	if (RIGHT(i) < r && smallest > a[RIGHT(i)]) {
		smallest = a[RIGHT(i)];
		smallest_index = RIGHT(i);
	}
	if (smallest_index != i) {
		swap(a[i], a[smallest_index]);
		max_heapify(a, l, r, smallest_index);
	}
}

void build_minheap(int* a, int l, int r) {
	for (int i = PARENT(r - 1); i >= l; --i) min_heapify(a, l, r, i);
}

void min_heapsort(int* a, int l, int r) {
	build_minheap(a, l, r);
	for (int i = r - 1; i >= l + 1; --i) {
		swap(a[l], a[i]);
		r--;
		min_heapify(a, l, r, l);
	}
}

int minheap_top(int* a, int l, int r) {
	if (r - l == 0) return INT_MAX;
	return a[l];
}

int minheap_pop(int* a, int l, int r) {
	if (r - l == 0) return INT_MAX;
	int min_val = a[l];
	a[l] = a[r - 1];
	min_heapify(a, l, r - 1, l);
	return min_val;
}

void minheap_push(int* a, int l, int r, int key) {
	a[r] = key;
	while (r > 0 && a[PARENT(r)] < a[r]) {
		swap(a[r], a[PARENT(r)]);
		r = PARENT(r);
	}
}