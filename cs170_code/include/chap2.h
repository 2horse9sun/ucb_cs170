#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// [l, r)
void swap(int* a, int i, int j);
int partition(int* a, int l, int r);
int randomized_partition(int* a, int l, int r);
void quicksort(int* a, int l, int r);
void randomized_quicksort(int* a, int l, int r);
void quicksort_test();
void mergesort(int* a, int l, int r);
void merge(int* a, int l, int m, int r);
void mergesort_test();

void gen_random_int_file(string file_name, long size);
int read_line(string file_name, int start, int num, int* buffer, bool reverse);
int write_line(string file_name, int num, int* buffer);
vector<string> external_conquer(string file_name, int* buffer);
int fill_input_buffer(vector<string> file_names, int** input_buffer, int* input_buffer_index, int* input_file_index);
int find_min(int** input_buffer, int* input_buffer_index, int file_num);
string merge_files(vector<string> file_names, int start, int size, int** input_buffer, int* output_buffer);
vector<string> external_merge(vector<string> file_names, int* buffer);
void external_mergesort(string file_name);
void external_mergesort_test();

pair<int, int> split(int* a, int l, int r, int val);
int select(int* a, int l, int r, int k);
void select_test();