#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
#include <stdio.h>
#include <random>
#include <cmath>
#include <math.h>
#include "../include/complex.h"
#include "../include/chap2.h"

using namespace std;

int PAGE_SIZE = 1024; // 4KB, one page need one I/O
int RAM_PAGE_NUM = 1000; // available RAM size

//const double PI = acos(-1.0);


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
	delete[] left;
	delete[] right;
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

//int read_line(string file_name, int start, int size, int* buffer, bool reverse = false) {
//	int line_num = 0;
//	fstream file(file_name, fstream::in);
//	file.seekg(ios::beg);
//	for (int i = 0; i < start; ++i) {
//		if (file.eof()) return 0;
//		file.ignore(numeric_limits<streamsize>::max(), '\n');
//	}
//	int num;
//	for (int i = 0; i < size; ++i) {
//		if (file >> num) {
//			line_num++;
//			buffer[i] = num;
//		}
//	}
//	if (reverse) {
//		int i = 0; int j = line_num-1;
//		while (i < j) {
//			int tmp = buffer[i];
//			buffer[i++] = buffer[j];
//			buffer[j--] = tmp;
//		}
//	}
//	return line_num;
//}

int read_line(fstream& file, int size, int* buffer, bool reverse = false) {
	int line_num = 0;
	int num;
	for (int i = 0; i < size; ++i) {
		if (file >> num) {
			line_num++;
			buffer[i] = num;
		}
	}
	if (reverse) {
		int i = 0; int j = line_num - 1;
		while (i < j) {
			int tmp = buffer[i];
			buffer[i++] = buffer[j];
			buffer[j--] = tmp;
		}
	}
	return line_num;
}

int write_line(fstream& file, int size, int* buffer) {
	int line_num = 0;
	file.seekg(ios::end);
	for (int i = 0; i < size; ++i) {
		line_num++;
		file << buffer[i];
		file << '\n';
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
	//int curr_file_index = 0;
	int sorted_file_num = 0;
	int line_num = 0;
	fstream rfile(file_name, fstream::in);
	while ((line_num = read_line(rfile, RAM_PAGE_NUM * PAGE_SIZE, buffer)) > 0) {
		//curr_file_index += line_num;
		mergesort(buffer, 0, line_num);
		string output_file_name = file_name + to_string(sorted_file_num++);
		fstream wfile(output_file_name, fstream::out | fstream::app);
		write_line(wfile, line_num, buffer);
		wfile.close();
		output_file_names.push_back(output_file_name);
	}
	rfile.close();
	return output_file_names;
}

int fill_input_buffer(fstream* rfiles, int file_num, int** input_buffer, int* input_buffer_index,  int* input_file_index) {
	int fill_num = 0;
	for (int i = 0; i < file_num; ++i) {
		if (input_buffer_index[i] == -1 && input_file_index[i] != -1) {
			int line_num = read_line(rfiles[i], PAGE_SIZE, input_buffer[i], true);
			fill_num += line_num;
			if (line_num < PAGE_SIZE) input_file_index[i] = -1; // indicate that input_file drains out
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

int flush_output_buffer(fstream& wfile, int* output_buffer, int output_buffer_index) {
	int flush_num = 0;
	int line_num = write_line(wfile, output_buffer_index, output_buffer);
	flush_num += line_num;
	return flush_num;
}

string merge_files(vector<string> file_names, int start, int size, int** input_buffer, int* output_buffer) {
	int file_num = min(size, (int)file_names.size() - start);
	vector<string> file_list;
	for (int i = 0; i < file_num; ++i) file_list.push_back(file_names[start + i]);
	// the smallest element's index in input_buffer[i]
	int* input_buffer_index = new int[file_num];
	for (int i = 0; i < file_num; ++i) input_buffer_index[i] = -1;
	// the current size of output_buffer
	int output_buffer_index = 0;
	// the next position to read in file_list[i]
	int* input_file_index = new int[file_num];
	for (int i = 0; i < file_num; ++i) input_file_index[i] = 0;

	string output_file_name = file_names[start] + to_string(start);
	fstream* rfiles = new fstream[file_num];
	for (int i = 0; i < file_num; ++i) rfiles[i] = fstream(file_list[i], fstream::in);
	fstream wfile(output_file_name, fstream::out | fstream::app);
	// first fill working input_buffers
	int input_buffer_size = fill_input_buffer(rfiles, file_num, input_buffer, input_buffer_index, input_file_index);
	// keep draining working input_buffers
	while (input_buffer_size > 0) {
		// fill the output_buffer till full
		while (output_buffer_index < PAGE_SIZE) {
			// find the smallest element in working input_buffers
			if (input_buffer_size > 0) {
				int min_index = find_min(input_buffer, input_buffer_index, file_num);
				output_buffer[output_buffer_index++] = input_buffer[min_index][input_buffer_index[min_index]];
				input_buffer_index[min_index]--;
				input_buffer_size--;
				// if one of the working input_buffers drains out, refill it
				if (input_buffer_index[min_index] < 0) {
					int fill_num = fill_input_buffer(rfiles, file_num, input_buffer, input_buffer_index, input_file_index);
					input_buffer_size += fill_num;
				}
			}
			// no element in working input_buffers
			else break;
		}
		// flush sorted elements into a new file
		flush_output_buffer(wfile, output_buffer, output_buffer_index);
		output_buffer_index = 0;
		// make sure input_files also drain out
		int fill_num = fill_input_buffer(rfiles, file_num, input_buffer, input_buffer_index, input_file_index);
		input_buffer_size += fill_num;
	}
	for (int i = 0; i < file_num; ++i) rfiles[i].close();
	wfile.close();
	delete[] rfiles;
	delete[] input_buffer_index;
	delete[] input_file_index;
	return output_file_name;
}

vector<string> external_merge(vector<string> file_names, int** input_buffer, int* output_buffer) {
	vector<string> output_file_names;
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
	// available RAM
	int* buffer = new int[RAM_PAGE_NUM * PAGE_SIZE];

	vector<string> output_file_names = external_conquer(file_name, buffer);

	int** input_buffer = new int* [RAM_PAGE_NUM - 1];
	for (int i = 0; i < RAM_PAGE_NUM - 1; ++i) input_buffer[i] = buffer + i * PAGE_SIZE;
	int* output_buffer = buffer + (RAM_PAGE_NUM - 1) * PAGE_SIZE;
	while (output_file_names.size() > 1) {
		output_file_names = external_merge(output_file_names, input_buffer, output_buffer);
	}
	remove((file_name + "_sorted").c_str());
	rename(output_file_names[0].c_str(), (file_name + "_sorted").c_str());

	delete[] input_buffer;
	delete[] buffer;
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



int find_nearest_two_pow(int len) {
	for (int i = 1; ; ++i) {
		int power = (int)pow(2, i);
		if (power >= len) {
			return power;
		}
	}
}


// n is power of 2, if not, add zeros
// n-point DFT
Complex* do_FFT(Complex* a, int n, double inverse) {
	if (n == 1) return a;
	Complex w_n(cos(inverse * 2 * PI / n), sin(inverse * 2 * PI / n));
	Complex w(1.0);
	Complex* a_e = new Complex[n / 2];
	Complex* a_o = new Complex[n / 2];
	Complex* y = new Complex[n];

	for (int i = 0; i < n; ++i) {
		if (i % 2 == 0) a_e[i / 2] = a[i];
		else a_o[i / 2] = a[i];
	}
	Complex* y_e = do_FFT(a_e, n / 2, inverse);
	Complex* y_o = do_FFT(a_o, n / 2, inverse);

	for (int i = 0; i < n / 2; ++i) {
		y[i] = y_e[i] + w * y_o[i];
		y[i + n / 2] = y_e[i] - w * y_o[i];
		w = w * w_n;
	}
	return y;
}

Complex* FFT(Complex* a, int n) {
	if (n == 1) return a;
	Complex* y = do_FFT(a, n, -1);
	return y;
}


Complex* IFFT(Complex* y, int n) {
	if (n == 1) return y;
	Complex* a = do_FFT(y, n, 1);
	for (int i = 0; i < n; ++i) a[i] = a[i] / (double)n;
	return a;
}