#ifndef complex_
#define complex_
#include<iostream>
using namespace std;

class Complex {
public:
	double real;
	double imaginary;

	Complex(): real(0.0), imaginary(0.0) {}
	Complex(double r, double i);
	Complex(const Complex& num);

	Complex& operator=(const Complex& num);
	Complex& operator=(double d);
	double norm2() const;
	double norm() const;
	Complex conjugate() const;
	bool operator==(const Complex& num) const;
	bool operator==(double d) const;
	Complex operator+(const Complex& num) const;
	Complex operator+(double d) const;
	friend Complex operator+(double d, const Complex& num);
	Complex operator-(const Complex& num) const;
	Complex operator-(double d) const;
	friend Complex operator-(double d, const Complex& num);
	// (a+bi)(c+di) = ac - bd + [(a+b)(c+d)-ac-bd]i
	Complex operator*(const Complex& num) const;
	Complex operator*(double num) const;
	friend Complex operator*(double d, const Complex& num);
	Complex operator/(Complex& num) const;
	Complex operator/(double num) const;
	friend Complex operator/(double d, Complex& num);

	operator double();

	friend ostream& operator<<(ostream& out, const Complex& num);

};




#endif
