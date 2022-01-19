#pragma once
#ifndef heap_
#define heap_
#include <iostream>

using namespace std;

inline int PARENT(int i);
inline int LEFT(int i);
inline int RIGHT(int i);

void max_heapify(int* a, int l, int r, int i);
void build_maxheap(int* a, int l, int r);
void max_heapsort(int* a, int l, int r);
int maxheap_top(int* a, int l, int r);
int maxheap_pop(int* a, int l, int r);
void maxheap_push(int* a, int l, int r, int key);


#endif