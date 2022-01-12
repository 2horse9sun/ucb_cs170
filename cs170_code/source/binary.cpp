#include<iostream>
#include<math.h>
#include "../include/binary.h"
using namespace std;

Binary::Binary() {
	MAX_LEN = 8;
	length = 0;
	arr = new int[MAX_LEN + 1];
}


Binary::Binary(const Binary& num) {
	length = num.length;
	MAX_LEN = num.MAX_LEN;
	arr = new int[MAX_LEN + 1];
	int i;
	for (i = 0; i < num.length; ++i) {
		arr[i] = num.arr[i];
	}
}

Binary::Binary(int d) {
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

Binary::~Binary() {
	delete[] arr;
}

// May overflow
long long Binary::get_value() const {
	long long res = 0;
	for (int i = 0; i < length; ++i) res += (arr[i] == 1 ? (i == 0 ? 1 : (2 << (i - 1))) : 0);
	return res;
}

void Binary::double_size() {
	MAX_LEN = 2 * MAX_LEN;
	int* new_arr = new int[this->MAX_LEN + 1];
	int i;
	for (i = 0; i < this->length; ++i) {
		new_arr[i] = arr[i];
	}
	delete[] arr;
	arr = new_arr;
}

Binary& Binary::operator=(const Binary& num) {
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

bool Binary::operator==(const Binary& num) const {
	if (length != num.length) return false;
	for (int i = 0; i < length; ++i) {
		if (arr[i] != num.arr[i]) return false;
	}
	return true;
}

bool Binary::operator>(const Binary& num) const {
	if (length < num.length) return false;
	if (length > num.length) return true;
	for (int i = length - 1; i >= 0; --i) {
		if (arr[i] < num.arr[i]) return false;
		if (arr[i] > num.arr[i]) return true;
	}
	return false;
}

bool Binary::operator<(const Binary& num) const {
	if (length < num.length) return true;
	if (length > num.length) return false;
	for (int i = length - 1; i >= 0; --i) {
		if (arr[i] < num.arr[i]) return true;
		if (arr[i] > num.arr[i]) return false;
	}
	return false;
}

Binary Binary::operator+(const Binary& num) const {
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
		int res = (i < a_len ? a[i] : 0) + (i < b_len ? b[i] : 0) + carry;
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

//Binary operator+(const Binary& num1, const Binary& num2) {
//	return num1 + num2;
//}

// Assume a>=b
Binary Binary::operator-(const Binary& num) const {
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
	while (i - 1 > 0 && c[i - 1] == 0) i--;
	subtraction.length = i;
	return subtraction;
}

//Binary operator-(const Binary& num1, const Binary& num2) {
//	return num1 - num2;
//}

Binary Binary::left_shift(int n = 1) const {
	if ((*this).is_zero()) return get_zero();
	Binary res = *this;
	while (res.length + 1 + n > res.MAX_LEN) res.double_size();
	res.length += n;
	int i;
	for (i = res.length - 1; i > n - 1; --i) res.arr[i] = res.arr[i - n];
	for (; i >= 0; --i) res.arr[i] = 0;
	return res;
}

Binary Binary::right_shift(int n = 1) const {
	Binary res = *this;
	if (res.length == 0) return res;
	if (res.length <= n) {
		res.length = 1;
		res.arr[0] = 0;
		return res;
	}
	res.length -= n;
	int i;
	for (i = 0; i < res.length; ++i) res.arr[i] = res.arr[i + n];
	return res;
}

// start from index n
Binary Binary::get_leftmost(int n) const {
	int new_length = length - n > 0 ? length - n : 0;
	if (new_length == 0) return get_zero();
	Binary left_half = Binary();
	while (left_half.MAX_LEN < new_length + 1) left_half.double_size();
	left_half.length = new_length;
	for (int i = 0; i < new_length; ++i) left_half.arr[i] = arr[i + n];
	return left_half;
}

// start from index 0
Binary Binary::get_rightmost(int n) const {
	int new_length = n;
	if (new_length == 0) return get_zero();
	Binary right_half = Binary();
	while (right_half.MAX_LEN < new_length + 1) right_half.double_size();
	right_half.length = new_length;
	for (int i = 0; i < new_length; ++i) right_half.arr[i] = arr[i];
	for (int i = new_length - 1; i > 0; --i) {
		if (right_half.arr[i] == 0) right_half.length--;
		else break;
	}
	return right_half;
}

bool Binary::is_zero() const {
	return length == 1 && arr[0] == 0;
}


bool Binary::is_even() const {
	return length > 0 && arr[0] == 0;
}

bool Binary::is_odd() const {
	return length > 0 && arr[0] == 1;
}

Binary Binary::multiply(const Binary& x, const Binary& y) const {
	if (y.is_zero()) return get_zero();
	Binary z = multiply(x, y.right_shift());
	if (y.is_even()) return z.left_shift();
	else return x + z.left_shift();
}

Binary Binary::multiply2(const Binary& x, const Binary& y) const {
	int n = max(x.length, y.length);
	if (n == 1) {
		if (x.is_zero() || y.is_zero()) return get_zero();
		else return get_one();
	}
	Binary xl = x.get_leftmost(n / 2);
	Binary xr = x.get_rightmost(n / 2);
	Binary yl = y.get_leftmost(n / 2);
	Binary yr = y.get_rightmost(n / 2);
	Binary P1 = multiply2(xl, yl);
	Binary P2 = multiply2(xr, yr);
	Binary P3 = multiply2(xl + xr, yl + yr);
	return P1.left_shift(n / 2).left_shift(n / 2) + (P3 - P1 - P2).left_shift(n / 2) + P2;
}

Binary Binary::operator*(const Binary& num) const {
	return multiply2(*this, num);
}


pair<Binary, Binary> Binary::divide(const Binary& x, const Binary& y) const {
	if (x.is_zero()) return make_pair(get_zero(), get_zero());
	pair<Binary, Binary> res = divide(x.right_shift(), y);
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

Binary Binary::operator/(const Binary& num) const {
	pair<Binary, Binary> res = divide(*this, num);
	return res.first;
}

Binary Binary::operator%(const Binary& num) const {
	pair<Binary, Binary> res = divide(*this, num);
	return res.second;
}



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
	while (i < j && i < len && j >= 0) {
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
