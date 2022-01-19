#pragma once
#ifndef chap2_
#define chap2_
#include <iostream>
#include <string>
#include <vector>
#include "./complex.h"
#include "../include/datetime.h"

using namespace std;

void matrix_multiplication_test();

// [l, r)
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
int read_line(fstream& file, int size, int* buffer, bool reverse);
int write_line(string file_name, int num, int* buffer);
// split big file into small sorted files
vector<string> external_conquer(string file_name, int* buffer);
int fill_input_buffer(fstream* rfiles, int file_num, int** input_buffer, int* input_buffer_index, int* input_file_index);
// naive k-way merge, could be refined
int find_min(int** input_buffer, int* input_buffer_index, int file_num);
int flush_output_buffer(fstream& wfile, int* output_buffer, int output_buffer_index);
string merge_files(vector<string> file_names, int start, int size, int** input_buffer, int* output_buffer);
vector<string> external_merge(vector<string> file_names, int** input_buffer, int* output_buffer);
void external_mergesort(string file_name);
void external_mergesort_test();

pair<int, int> split(int* a, int l, int r, int val);
int quickselect(int* a, int l, int r, int k);
void quickselect_test();
int median(int* a, int l, int r);
int* quantile(int* a, int l, int r, int k);
void quantile_test();

void FFT_test();
void polynomial_multiplication_test();

void counting_sort(int* a, int n, int k);
void counting_sort_test();
void radix_sort_datetime(DateTime** dts, int n);
void radix_sort_datetime_test();

int select_from_two_sorted_array(int* a, int la, int ra, int* b, int lb, int rb, int k);
void select_from_two_sorted_array_test();

bool major_element(int* a, int l, int r, int* major);
bool major_element2(int* a, int n, int* major);
void major_element_test();
#endif