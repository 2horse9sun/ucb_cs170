#ifndef integer_
#define integer_
#include<iostream>
#include<math.h>
using namespace std;

class Binary {
public:
	int* arr;
	int length;
	int MAX_LEN;


	Binary() {
		MAX_LEN = 8;
		length = 0;
		arr = new int[MAX_LEN + 1];
	}


	Binary(const Binary& num) {
		length = num.length;
		MAX_LEN = num.MAX_LEN;
		arr = new int[MAX_LEN+1]; 
		int i;
		for (i = 0; i < num.length; ++i) {
			arr[i] = num.arr[i];
		}
	}

	Binary(int d) {
		MAX_LEN = 64;
		arr = new int[MAX_LEN + 1];
		arr[0] = 0;
		int i = 0;
		int q;
		int r;
		while (d > 0) {
			q = d / 2;
			r = d % 2;
			if (r == 0) arr[i] = 0;
			else arr[i] = 1;
			d = q;
			i++;
		}
		length = i;
	}

	~Binary() {
		delete[] arr;
	}

	// May overflow
	long long get_value() {
		long long res = 0;
		for (int i = 0; i < length; ++i) res += (arr[i] == 1 ? (i==0?1:(2<<(i-1))) : 0);
		return res;
	}

	void double_size() {
		MAX_LEN = 2 * MAX_LEN;
		int* new_arr = new int[this->MAX_LEN + 1];
		int i;
		for (i = 0; i < this->length; ++i) {
			new_arr[i] = arr[i];
		}
		delete[] arr;
		arr = new_arr;
	}

	Binary& operator=(const Binary& num) {
		if (this != &num) {
			length = num.length;
			MAX_LEN = num.MAX_LEN;
			arr = new int[MAX_LEN + 1];
			int i;
			for (i = 0; i < num.length; ++i) {
				arr[i] = num.arr[i];
			}
		}
		return *this;
	}

	bool operator==(const Binary& num) {
		if (length != num.length) return false;
		for (int i = 0; i < length; ++i) {
			if (arr[i] != num.arr[i]) return false;
		}
		return true;
	}

	bool operator>(const Binary& num) {
		if (length < num.length) return false;
		if (length > num.length) return true;
		for (int i = length-1; i >= 0; --i) {
			if (arr[i] < num.arr[i]) return false;
			if (arr[i] > num.arr[i]) return true;
		}
		return false;
	}

	bool operator<(const Binary& num) {
		if (length < num.length) return true;
		if (length > num.length) return false;
		for (int i = length - 1; i >= 0; --i) {
			if (arr[i] < num.arr[i]) return true;
			if (arr[i] > num.arr[i]) return false;
		}
		return false;
	}

	Binary operator+(const Binary& num) {
		int* a = arr;
		int a_len = length;
		int* b = num.arr;
		int b_len = num.length;
		Binary addition = Binary();
		while (addition.MAX_LEN < max(a_len, b_len) + 2) addition.double_size();

		int* c = addition.arr;
		int carry = 0;
		int i;
		for (i = 0; i < max(a_len, b_len); ++i) {
			int res = (i<a_len?a[i]:0) + (i<b_len?b[i]:0) + carry;
			carry = 0;
			if (res > 1) {
				carry = 1;
				res -= 2;
			}
			c[i] = res;
		}
		if (carry == 1) {
			c[i] = 1;
			i++;
		}
		addition.length = i;
		return addition;
	}

	// Assume a>=b
	Binary operator-(const Binary& num) {
		int* a = arr;
		int a_len = length;
		int* b = num.arr;
		int b_len = num.length;
		Binary subtraction = Binary();
		while (subtraction.MAX_LEN < max(a_len, b_len) + 2) subtraction.double_size();

		int* c = subtraction.arr;
		int carry = 0;
		int i;
		for (i = 0; i < max(a_len, b_len); ++i) {
			int minuend = i < a_len ? a[i] : 0;
			int subtrahend = (i < b_len ? b[i] : 0) + carry;
			carry = 0;
			if (minuend < subtrahend) {
				carry = 1;
				minuend += 2;
			}
			int res = minuend - subtrahend;
			c[i] = res;
		}
		while (i-1 > 0 && c[i-1] == 0) i--;
		subtraction.length = i;
		return subtraction;
	}

	Binary left_shift() {
		if ((*this).is_zero()) return get_zero();
		Binary res = *this;
		while (res.length + 2 > res.MAX_LEN) res.double_size();
		res.length++;
		int i;
		for (i = res.length-1; i > 0; --i) res.arr[i] = res.arr[i - 1];
		res.arr[0] = 0;
		return res;
	}

	Binary right_shift() {
		Binary res = *this;
		if (res.length == 0) return res;
		if (res.length == 1) {
			res.arr[0] = 0;
			return res;
		}
		res.length--;
		int i;
		for (i = 0; i < res.length; ++i) res.arr[i] = res.arr[i+1];
		return res;
	}

	bool is_zero() {
		return length == 1 && arr[0] == 0;
	}

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

	bool is_even() {
		return length > 0 && arr[0] == 0;
	}

	bool is_odd() {
		return length > 0 && arr[0] == 1;
	}

	Binary multiply(Binary& x, Binary& y) {
		if (y.is_zero()) return get_zero();
		Binary yy = y.right_shift();
		Binary z = multiply(x, yy);
		if (y.is_even()) return z.left_shift();
		else return x + z.left_shift();
	}

	Binary operator*(Binary& num) {
		return multiply(*this, num);
	}

	pair<Binary, Binary> divide(Binary& x, Binary& y) {
		if (x.is_zero()) return make_pair(get_zero(), get_zero());
		Binary xx = x.right_shift();
		pair<Binary, Binary> res = divide(xx, y);
		Binary q = res.first;
		Binary r = res.second;
		q = q.left_shift();
		r = r.left_shift();
		if (x.is_odd()) r = r + get_one();
		if (r > y || r == y) {
			r = r - y;
			q = q + get_one();
		}
		return make_pair(q, r);
	}

	Binary operator/(Binary& num) {
		pair<Binary, Binary> res = divide(*this, num);
		return res.first;
	}

	Binary operator%(Binary& num) {
		pair<Binary, Binary> res = divide(*this, num);
		return res.second;
	}

};

// Input: a binary number
// Without an input checker
istream& operator>>(istream& in, Binary& num) {
	int len = 0;
	char c;
	while ((c = in.get()) != '\n') {
		while (num.MAX_LEN < len + 2) num.double_size();
		num.arr[len] = c - '0';
		len++;
		num.length = len;
	}
	int i = 0;
	int j = len - 1;
	char tmp;
	while (i < j && i<len && j>=0) {
		tmp = num.arr[i];
		num.arr[i] = num.arr[j];
		num.arr[j] = tmp;
		i++; j--;
	}
	return in;
}

ostream& operator<<(ostream& out, const Binary& num) {
	if (num.length == 0) {
		out << "NULL";
		return out;
	}
	for (int i = num.length - 1; i >= 0; --i)
	{
		out << num.arr[i];
	}
	return out;
}


#endif
