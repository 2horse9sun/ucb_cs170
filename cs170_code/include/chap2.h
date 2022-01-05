#pragma once
#include <iostream>

using namespace std;

// [l, r)
void mergesort(int* a, int l, int r);
void merge(int* a, int l, int m, int r);
void mergesort_test();
void swap(int* a, int i, int j);
int partition(int* a, int l, int r);
int randomized_partition(int* a, int l, int r);
void quicksort(int* a, int l, int r);
void randomized_quicksort(int* a, int l, int r);
void quicksort_test();

pair<int, int> split(int* a, int l, int r, int val);
int select(int* a, int l, int r, int k);
void select_test();