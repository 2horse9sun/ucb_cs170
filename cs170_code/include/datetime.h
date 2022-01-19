#ifndef datetime_
#define datetime_
#include<iostream>
using namespace std;

class DateTime {
public:
	int y;
	int M;
	int d;
	int H;
	int m;
	int s;

	DateTime(int y, int M, int d, int H, int m, int s) : y(y), M(M), d(d), H(H), m(m), s(s) {}

	friend ostream& operator<<(ostream& out, const DateTime& dt);
	friend ostream& operator<<(ostream& out, const DateTime* dt);

};

void counting_sort_y(DateTime** a, int n);
void counting_sort_M(DateTime** a, int n);
void counting_sort_d(DateTime** a, int n);
void counting_sort_H(DateTime** a, int n);
void counting_sort_m(DateTime** a, int n);
void counting_sort_s(DateTime** a, int n);


#endif
