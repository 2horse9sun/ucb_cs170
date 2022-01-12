#ifndef binary_
#define binary_
#include <iostream>

using namespace std;

class Binary {
public:
	int* arr;
	int length;
	int MAX_LEN;

	Binary();
	Binary(const Binary& num);
	Binary(int d);
	~Binary();

	// May overflow
	long long get_value() const;
	void double_size();

	Binary& operator=(const Binary& num);
	bool operator==(const Binary& num) const;
	bool operator>(const Binary& num) const;
	bool operator<(const Binary& num) const;
	Binary operator+(const Binary& num) const;
	// Assume a>=b
	Binary operator-(const Binary& num) const;

	Binary left_shift(int n) const;
	Binary right_shift(int n) const;
	// start from index n
	Binary get_leftmost(int n) const;
	// start from index 0
	Binary get_rightmost(int n) const;
	bool is_zero() const;

	static Binary get_zero() {
		Binary zero = Binary();
		zero.length = 1;
		zero.arr[0] = 0;
		return zero;
	}
	static Binary get_one() {
		Binary one = Binary();
		one.length = 1;
		one.arr[0] = 1;
		return one;
	}

	bool is_even() const;
	bool is_odd() const;

	Binary multiply(const Binary& x, const Binary& y) const;
	Binary multiply2(const Binary& x, const Binary& y) const;
	Binary operator*(const Binary& num) const;
	pair<Binary, Binary> divide(const Binary& x, const Binary& y) const;
	Binary operator/(const Binary& num) const;
	Binary operator%(const Binary& num) const;

	// Input: a binary number
    // Without an input checker
	friend istream& operator>>(istream& in, Binary& num);
	friend ostream& operator<<(ostream& out, const Binary& num);
};

#endif
