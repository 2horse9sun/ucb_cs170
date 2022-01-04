#pragma once
#include <iostream>

using namespace std;

// [l, r)
void mergesort(int* a, int l, int r);
void merge(int* a, int l, int m, int r);
void mergesort_test();