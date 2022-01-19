#include<iostream>
#include "../include/datetime.h"
using namespace std;

ostream& operator<<(ostream& out, const DateTime& dt) {
	out << dt.y << "-" << dt.M << "-" << dt.d << " " << dt.H << ":" << dt.m << ":" << dt.s;
	return out;
}

ostream& operator<<(ostream& out, const DateTime* dt) {
	out << dt->y << "-" << dt->M << "-" << dt->d << " " << dt->H << ":" << dt->m << ":" << dt->s;
	return out;
}

void counting_sort_y(DateTime** a, int n) {
	int k = 2099;
	DateTime** b = new DateTime * [n];
	int* c = new int[k + 1];
	for (int i = 0; i <= k; ++i) c[i] = 0;
	for (int i = 0; i < n; ++i) c[a[i]->y]++;
	for (int i = 1; i <= k; ++i) c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; --i) {
		b[c[a[i]->y] - 1] = a[i];
		c[a[i]->y]--;
	}
	for (int i = 0; i < n; ++i) a[i] = b[i];
	delete[] b; delete[] c;
}

void counting_sort_M(DateTime** a, int n) {
	int k = 12;
	DateTime** b = new DateTime*[n];
	int* c = new int[k + 1];
	for (int i = 0; i <= k; ++i) c[i] = 0;
	for (int i = 0; i < n; ++i) c[a[i]->M]++;
	for (int i = 1; i <= k; ++i) c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; --i) {
		b[c[a[i]->M] - 1] = a[i];
		c[a[i]->M]--;
	}
	for (int i = 0; i < n; ++i) a[i] = b[i];
	delete[] b; delete[] c;
}

void counting_sort_d(DateTime** a, int n) {
	int k = 31;
	DateTime** b = new DateTime*[n];
	int* c = new int[k + 1];
	for (int i = 0; i <= k; ++i) c[i] = 0;
	for (int i = 0; i < n; ++i) c[a[i]->d]++;
	for (int i = 1; i <= k; ++i) c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; --i) {
		b[c[a[i]->d] - 1] = a[i];
		c[a[i]->d]--;
	}
	for (int i = 0; i < n; ++i) a[i] = b[i];
	delete[] b; delete[] c;
}

void counting_sort_H(DateTime** a, int n) {
	int k = 23;
	DateTime** b = new DateTime*[n];
	int* c = new int[k + 1];
	for (int i = 0; i <= k; ++i) c[i] = 0;
	for (int i = 0; i < n; ++i) c[a[i]->H]++;
	for (int i = 1; i <= k; ++i) c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; --i) {
		b[c[a[i]->H] - 1] = a[i];
		c[a[i]->H]--;
	}
	for (int i = 0; i < n; ++i) a[i] = b[i];
	delete[] b; delete[] c;
}

void counting_sort_m(DateTime** a, int n) {
	int k = 59;
	DateTime** b = new DateTime*[n];
	int* c = new int[k + 1];
	for (int i = 0; i <= k; ++i) c[i] = 0;
	for (int i = 0; i < n; ++i) c[a[i]->m]++;
	for (int i = 1; i <= k; ++i) c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; --i) {
		b[c[a[i]->m] - 1] = a[i];
		c[a[i]->m]--;
	}
	for (int i = 0; i < n; ++i) a[i] = b[i];
	delete[] b; delete[] c;
}

void counting_sort_s(DateTime** a, int n) {
	int k = 59;
	DateTime** b = new DateTime*[n];
	int* c = new int[k + 1];
	for (int i = 0; i <= k; ++i) c[i] = 0;
	for (int i = 0; i < n; ++i) c[a[i]->s]++;
	for (int i = 1; i <= k; ++i) c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; --i) {
		b[c[a[i]->s] - 1] = a[i];
		c[a[i]->s]--;
	}
	for (int i = 0; i < n; ++i) a[i] = b[i];
	delete[] b; delete[] c;
}