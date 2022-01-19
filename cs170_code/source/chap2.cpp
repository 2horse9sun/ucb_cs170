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
#include "../include/chap2.h"
#include "../include/datetime.h"

using namespace std;

int PAGE_SIZE = 1024; // 4KB, one page need one I/O
int RAM_PAGE_NUM = 1000; // available RAM size




int partition(int* a, int l, int r) {
	int p = a[r - 1];
	int i = l - 1;
	for (int j = l; j < r - 1; ++j) {
		if (a[j] <= p) {
			i++;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[r - 1]);
	return i + 1;
}

int randomized_partition(int* a, int l, int r) {
	int m = rand() % (r - l) + l;
	swap(a[m], a[r - 1]);
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

// one pass
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


// in place
pair<int, int> split(int* a, int l, int r, int val) {
	int k = l;
	for (int i = l; i < r; ++i) {
		if (a[i] < val) {
			swap(a[k], a[i]);
			k++;
		}
	}
	int lb = k;
	for (int i = k; i < r; ++i) {
		if (a[i] == val) {
			swap(a[k], a[i]);
			k++;
		}
	}
	int ub = k;
	return make_pair(lb, ub);
}

// k'th smallest element, in place, original array will change
int quickselect(int* a, int l, int r, int k) {
	int val = a[rand() % (r - l) + l];
	pair<int, int> res = split(a, l, r, val);
	int lb = res.first; int ub = res.second;
	if (k <= lb - l) return quickselect(a, l, lb, k);
	else if (k > ub - l) return quickselect(a, ub, r, k - ub + l);
	else return val;
}

int median(int* a, int l, int r) {
	return quickselect(a, l, r, ((r - l) + 1) / 2);
}

// k > 1
int* quantile(int* a, int l, int r, int k) {
	int n = r - l;
	if (k == 2) {
		int* res = new int[1];
		res[0] = median(a, l, r);
		return res;
	}
	if (k % 2 == 0) {
		int m = median(a, l, r);
		int* left = quantile(a, l, l + (n + 1) / 2, k / 2);
		int* right = quantile(a, l + (n + 1) / 2, r, k / 2);
		int* res = new int[k - 1];
		int i = 0;
		for (; i < k / 2 - 1; ++i) res[i] = left[i];
		res[i++] = m;
		for (; i < k - 1; ++i) res[i] = right[i-k/2];
		delete[] left; delete[] right;
		return res;
	} else {
		int q = quickselect(a, l, r, n / k);
		int* right = quantile(a, l + n / k, r, k - 1);
		int* res = new int[k - 1];
		res[0] = q;
		for (int i = 1; i < k - 1; ++i) res[i] = right[i - 1];
		delete[] right;
		return res;
	}
}


void counting_sort(int* a, int n, int k) {
	int* b = new int[n];
	int* c = new int[k+1];
	for (int i = 0; i <= k; ++i) c[i] = 0;
	for (int i = 0; i < n; ++i) c[a[i]]++;
	for (int i = 1; i <= k; ++i) c[i] += c[i-1];
	for (int i = n-1; i >= 0; --i) {
		b[c[a[i]]-1] = a[i];
		c[a[i]]--;
	}
	for (int i = 0; i < n; ++i) a[i] = b[i];
	delete[] b; delete[] c;
}


void radix_sort_datetime(DateTime** dts, int n) {
	counting_sort_s(dts, n);
	counting_sort_m(dts, n);
	counting_sort_H(dts, n);
	counting_sort_d(dts, n);
	counting_sort_M(dts, n);
	counting_sort_y(dts, n);
}


int select_from_two_sorted_array(int* a, int la, int ra, int* b, int lb, int rb, int k) {
	int na = ra - la;
	int nb = rb - lb;
	if (k == 1) return min(na > 0 ? a[la] : INT_MAX, nb > 0 ? b[lb] : INT_MAX);
	int kf = k / 2;
	int kc = k % 2 == 0 ? k / 2 : (k + 1) / 2;
	int am = la + kf - 1 < ra ? a[la + kf - 1] : INT_MAX;
	int bm = lb + kc - 1 < rb ? b[lb + kc - 1] : INT_MAX;
	if (am == bm) return am;
	else if (am > bm) return select_from_two_sorted_array(a, la, min(la + kf, ra), b, min(lb + kc, rb), rb, kf);
	else return select_from_two_sorted_array(a, min(la + kf, ra), ra, b, lb, min(lb + kc, rb), kc);
}




bool major_element(int* a, int l, int r, int* major) {
	if (r - l == 0) return false;
	if (r - l == 1) {
		*major = a[l];
		return true;
	}
	int m = l + (r - l) / 2;
	int* major1 = new int; 
	int* major2 = new int; 
	if (major_element(a, l, m, major1)) {
		int cnt = 0;
		for (int i = l; i < r; ++i) {
			if (a[i] == *major1) cnt++;
		}
		if (cnt >= m + 1) {
			*major = *major1; 
			delete major1; delete major2; 
			return true;
		}
	}
	if (major_element(a, m, r, major2)) {
		int cnt = 0;
		for (int i = l; i < r; ++i) {
			if (a[i] == *major2) cnt++;
		}
		if (cnt >= m + 1) {
			*major = *major2; 
			delete major1; delete major2; 
			return true;
		}
	}
	return false;
}

bool major_element2(int* a, int n, int* major) {
	if (n == 0) return false;
	if (n == 1) {
		*major = a[0];
		return true;
	}
	if (n % 2 == 0) {
		int* aa = new int[n / 2];
		int k = 0;
		for (int i = 0; i < n; i += 2) {
			if (a[i] == a[i + 1]) aa[k++] = a[i];
		}
		bool res = major_element2(aa, k, major);
		delete[] aa;
		return res;
	} else {
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			if (a[i] == a[n-1]) cnt++;
		}
		if (cnt >= n / 2 + 1) {
			*major = a[n-1];
			return true;
		}
		else return major_element2(a, n - 1, major);
	}
}