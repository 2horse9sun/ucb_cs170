#include<iostream>
#include<math.h>
#include<cmath>
#include "../include/global.h"
#include "../include/complex.h"
using namespace std;


Complex::Complex(double r, double i = 0.0) {
	real = r;
	imaginary = i;
	if (real < err && real > -err) {
		real = 0;
	}
	if (imaginary < err && imaginary > -err) {
		imaginary = 0;
	}
}

Complex::Complex(const Complex& num) {
	real = num.real;
	imaginary = num.imaginary;
}

Complex& Complex::operator=(const Complex& num) {
	if (this != &num) {
		real = num.real;
		imaginary = num.imaginary;
	}
	return *this;
}

Complex& Complex::operator=(double d) {
	real = d;
	imaginary = 0.0;
	if (real < err && real > -err) {
		real = 0;
	}
	return *this;
}

double Complex::norm2() const{
	return real * real + imaginary * imaginary;
}

double Complex::norm() const{
	return sqrt(real * real + imaginary * imaginary);
}

Complex Complex::conjugate() const{
	return Complex(real, -imaginary);
}

bool Complex::operator==(const Complex& num) const{
	return real == num.real && imaginary == num.imaginary;
}

bool Complex::operator==(double d) const{
	return real == d && imaginary == 0.0;
}

Complex Complex::operator+(const Complex& num) const{
	return Complex(real + num.real, imaginary + num.imaginary);
}


Complex Complex::operator+(double d) const{
	return Complex(real + d, imaginary);
}

Complex operator+(double d, const Complex& num) {
	return num + d;
}

Complex Complex::operator-(const Complex& num) const{
	return Complex(real - num.real, imaginary - num.imaginary);
}


Complex Complex::operator-(double d) const{
	return Complex(real - d, imaginary);
}

Complex operator-(double d, const Complex& num) {
	return Complex(d - num.real, -num.imaginary);
}

// (a+bi)(c+di) = ac - bd + [(a+b)(c+d)-ac-bd]i
Complex Complex::operator*(const Complex& num) const{
	double ac = real * num.real; double bd = imaginary * num.imaginary;
	double abcd = (real + imaginary) * (num.real + num.imaginary);
	return Complex(ac - bd, abcd - ac - bd);
}


Complex Complex::operator*(double num) const{
	return Complex(real * num, imaginary * num);
}

Complex operator*(double d, const Complex& num) {
	return num * d;
}

Complex Complex::operator/(Complex& num) const{
	Complex num_conjugate = num.conjugate();
	return ((*this) * (num_conjugate)) * (1.0 / num.norm2());
}


Complex Complex::operator/(double num) const{
	return Complex(real / num, imaginary / num);
}

Complex operator/(double d, Complex& num) {
	Complex num_conjugate = num.conjugate();
	return (d * num_conjugate) * (1.0 / num.norm2());
}

Complex::operator double() {
	if (real < err && real > -err) {
		real = 0;
	}
	return real;
}

ostream& operator<<(ostream& out, const Complex& num) {
	out << num.real << ((num.imaginary < 0) ? "" : "+") << num.imaginary << "i" << endl;
	return out;
}