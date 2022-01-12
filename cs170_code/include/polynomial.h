#ifndef polynomial_
#define polynomial_
#include<iostream>
using namespace std;

class Polynomial {
public:
	// coefficients: a[0] + a[1]x + a[2]x^2 + ... + a[len-1]x^(len-1)
	double* a;
	// degree = len - 1
	int len;

	
	Polynomial(double* input, int input_len);
	Polynomial(const Polynomial& p);
	~Polynomial();

	double get_value(double x) const;

	Polynomial& operator=(const Polynomial& p);
	bool operator==(const Polynomial& p) const;
	Polynomial operator+(const Polynomial& p) const;
	Polynomial operator-(const Polynomial& p) const;

	Polynomial multiplication_FFT(const Polynomial& p1, const Polynomial& p2) const;
	Polynomial operator*(const Polynomial& p) const;

	friend ostream& operator<<(ostream& out, const Polynomial& p);

};




#endif
