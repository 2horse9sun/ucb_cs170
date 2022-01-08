#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
#include <stdio.h>
#include <random>
#include "../include/chap2.h"

using namespace std;

int PAGE_SIZE = 1024; // 4KB
int RAM_PAGE_NUM = 1000;



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

void merge(int* a, int l, int m, int r) {
	int* left = new int[m - l];
	int* right = new int[r - m];
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


void gen_random_int_file(string file_name, long size) {
	fstream file(file_name, fstream::out | fstream::trunc);
	/* Seed */
	random_device rd;
	/* Random number generator */
	default_random_engine generator(rd());
	/* Distribution on which to apply the generator */
	uniform_int_distribution<int> distribution(0, INT_MAX);
	for (long i = 0; i < size; ++i) {
		file << distribution(generator);
		file << '\n';
	}
	cout << "random file generated!" << endl;
}

int read_line(string file_name, int start, int size, int* buffer, bool reverse = false) {
	int line_num = 0;
	fstream file(file_name, fstream::in);
	file.seekg(ios::beg);
	for (int i = 0; i < start; ++i) {
		if (file.eof()) return 0;
		file.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	int num;
	for (int i = 0; i < size; ++i) {
		if (file >> num) {
			line_num++;
			buffer[i] = num;
		}
	}
	if (reverse) {
		int i = 0; int j = line_num-1;
		while (i < j) {
			int tmp = buffer[i];
			buffer[i++] = buffer[j];
			buffer[j--] = tmp;
		}
	}
	return line_num;
}

int write_line(string file_name, int size, int* buffer) {
	int line_num = 0;
	fstream file(file_name, fstream::out | fstream::app);
	file.seekg(ios::end);
	for (int i = 0; i < size; ++i) {
		line_num++;
		file << buffer[i];
		file << '\n';
	}
	return line_num;
}


vector<string> external_conquer(string file_name, int* buffer) {
	vector<string> output_file_names;
	int curr_file_index = 0;
	int sorted_file_num = 0;
	int line_num = 0;
	while ((line_num = read_line(file_name, curr_file_index, RAM_PAGE_NUM * PAGE_SIZE, buffer)) > 0) {
		curr_file_index += line_num;
		mergesort(buffer, 0, line_num);
		string output_file_name = file_name + to_string(sorted_file_num++);
		write_line(output_file_name, line_num, buffer);
		output_file_names.push_back(output_file_name);
	}
	return output_file_names;
}

int fill_input_buffer(vector<string> file_names, int** input_buffer, int* input_buffer_index,  int* input_file_index) {
	int fill_num = 0;
	int file_num = file_names.size();
	for (int i = 0; i < file_num; ++i) {
		if (input_buffer_index[i] == -1 && input_file_index[i] != -1) {
			int line_num = read_line(file_names[i], input_file_index[i] * PAGE_SIZE, PAGE_SIZE, input_buffer[i], true);
			fill_num += line_num;
			if (line_num < PAGE_SIZE) input_file_index[i] = -1;
			else input_file_index[i]++;
			input_buffer_index[i] = line_num - 1;
		}
	}
	return fill_num;
}

int find_min(int** input_buffer, int* input_buffer_index, int file_num) {
	int min_val = INT_MAX;
	int min_index = -1;
	for (int i = 0; i < file_num; ++i) {
		if (input_buffer_index[i] >= 0 && input_buffer[i][input_buffer_index[i]] < min_val) {
			min_val = input_buffer[i][input_buffer_index[i]];
			min_index = i;
		}
	}
	return min_index;
}

int flush_output_buffer(string output_file_name, int* output_buffer, int output_buffer_index) {
	int flush_num = 0;
	int line_num = write_line(output_file_name, output_buffer_index, output_buffer);
	flush_num += line_num;
	return flush_num;
}

string merge_files(vector<string> file_names, int start, int size, int** input_buffer, int* output_buffer) {
	int file_num = min(size, (int)file_names.size() - start);
	vector<string> file_list;
	for (int i = 0; i < file_num; ++i) file_list.push_back(file_names[start + i]);
	int* input_buffer_index = new int[file_num];
	for (int i = 0; i < file_num; ++i) input_buffer_index[i] = -1;
	int output_buffer_index = 0;
	int* input_file_index = new int[file_num];
	for (int i = 0; i < file_num; ++i) input_file_index[i] = 0;

	string output_file_name = file_names[start] + to_string(start);
	int input_buffer_size = fill_input_buffer(file_list, input_buffer, input_buffer_index, input_file_index);
	while (input_buffer_size > 0) {
		while (output_buffer_index < PAGE_SIZE) {
			if (input_buffer_size > 0) {
				int min_index = find_min(input_buffer, input_buffer_index, file_num);
				output_buffer[output_buffer_index++] = input_buffer[min_index][input_buffer_index[min_index]];
				input_buffer_index[min_index]--;
				input_buffer_size--;
				if (input_buffer_index[min_index] < 0) {
					int fill_num = fill_input_buffer(file_list, input_buffer, input_buffer_index, input_file_index);
					input_buffer_size += fill_num;
				}
			}
			else break;
		}
		flush_output_buffer(output_file_name, output_buffer, output_buffer_index);
		output_buffer_index = 0;
		int fill_num = fill_input_buffer(file_list, input_buffer, input_buffer_index, input_file_index);
		input_buffer_size += fill_num;
	}
	return output_file_name;
}

vector<string> external_merge(vector<string> file_names, int* buffer) {
	vector<string> output_file_names;
	int** input_buffer = new int* [RAM_PAGE_NUM - 1];
	for (int i = 0; i < RAM_PAGE_NUM - 1; ++i) input_buffer[i] = buffer + i * PAGE_SIZE;
	int* output_buffer = buffer + (RAM_PAGE_NUM - 1) * PAGE_SIZE;

	int file_num = file_names.size();
	int merge_times = file_num / (RAM_PAGE_NUM - 1) + (file_num % (RAM_PAGE_NUM - 1) == 0 ? 0 : 1);
	for (int i = 0; i < merge_times; ++i) {
		output_file_names.push_back(
			merge_files(file_names, i*(RAM_PAGE_NUM - 1), RAM_PAGE_NUM - 1, input_buffer, output_buffer)
		);
	}
	
	for (string file_name : file_names) remove(file_name.c_str());
	return output_file_names;

}


void external_mergesort(string file_name) {
	int* buffer = new int[RAM_PAGE_NUM * PAGE_SIZE];

	vector<string> output_file_names = external_conquer(file_name, buffer);

	while (output_file_names.size() > 1) {
		output_file_names = external_merge(output_file_names, buffer);
	}
	remove((file_name + "_sorted").c_str());
	rename(output_file_names[0].c_str(), (file_name + "_sorted").c_str());
	
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