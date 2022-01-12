#ifndef complex_
#define complex_
#include<iostream>
#include<math.h>
#include<cmath>
#include "../include/constant.h"
using namespace std;

class Complex {
public:
	double real;
	double imaginary;


	Complex(): real(0.0), imaginary(0.0) {}

	Complex(double r, double i = 0.0) {
		real = r;
		imaginary = i;
		if (real < err && real > -err) {
			real = 0;
		}
		if (imaginary < err && imaginary > -err) {
			imaginary = 0;
		}
	}

	Complex(const Complex& num) {
		real = num.real;
		imaginary = num.imaginary;
	}

	Complex& operator=(const Complex& num) {
		if (this != &num) {
			real = num.real;
			imaginary = num.imaginary;
		}
		return *this;
	}

	Complex& operator=(double d) {
		real = d;
		imaginary = 0.0;
		if (real < err && real > -err) {
			real = 0;
		}
		return *this;
	}

	double norm2() {
		return real * real + imaginary * imaginary;
	}

	double norm() {
		return sqrt(real * real + imaginary * imaginary);
	}

	Complex conjugate() {
		return Complex(real, -imaginary);
	}

	bool operator==(const Complex& num) {
		return real==num.real && imaginary==num.imaginary;
	}

	bool operator==(double d) {
		return real == d && imaginary == 0.0;
	}

	Complex operator+(const Complex& num) {
		return Complex(real+num.real, imaginary+num.imaginary);
	}

	friend Complex operator+(const Complex& num1, const Complex& num2) {
		return num1 + num2;
	}

	Complex operator+(double d) {
		return Complex(real + d, imaginary);
	}

	friend Complex operator+(double d, const Complex& num) {
		return num + d;
	}

	Complex operator-(const Complex& num) {
		return Complex(real - num.real, imaginary - num.imaginary);
	}

	friend Complex operator-(const Complex& num1, const Complex& num2) {
		return num1 - num2;
	}

	Complex operator-(double d) {
		return Complex(real - d, imaginary);
	}

	friend Complex operator-(double d, const Complex& num) {
		return Complex(d - num.real, -num.imaginary);
	}

	// (a+bi)(c+di) = ac - bd + [(a+b)(c+d)-ac-bd]i
	Complex operator*(const Complex& num) {
		double ac = real * num.real; double bd = imaginary * num.imaginary;
		double abcd = (real + imaginary) * (num.real + num.imaginary);
		return Complex(ac - bd, abcd - ac - bd);
	}

	friend Complex operator*(const Complex& num1, const Complex& num2) {
		return num1 * num2;
	}

	Complex operator*(double num) {
		return Complex(real*num, imaginary*num);
	}

	friend Complex operator*(double d, const Complex& num) {
		return num * d;
	}

	Complex operator/(Complex& num) {
		Complex num_conjugate = num.conjugate();
		return ((*this) * (num_conjugate)) * (1.0 / num.norm2());
	}

	friend Complex operator/(const Complex& num1, const Complex& num2) {
		return num1 / num2;
	}

	Complex operator/(double num) {
		return Complex(real / num, imaginary / num);
	}

	friend Complex operator/(double d, Complex& num) {
		Complex num_conjugate = num.conjugate();
		return (d * num_conjugate) * (1.0 / num.norm2());
	}

	operator double() {
		if (real < err && real > -err) {
			real = 0;
		}
		return real;
	}

	friend ostream& operator<<(ostream& out, const Complex& num) {
		out << num.real << ((num.imaginary < 0) ? "" : "+") << num.imaginary << "i" << endl;
		return out;
	}

};




#endif
