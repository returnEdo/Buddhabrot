#include "Complex.h"

#include <cassert>


Complex::Complex(double a_, double b_):
	a(a_), b(b_)	{}

Complex::Complex(void):
	Complex(.0, .0)	{}

Complex::Complex(const Complex& other):
	Complex(other.a, other.b)	{}


/* operations */

void Complex::operator =(const Complex& c){

	a = c.a;
	b = c.b;
}

/* with complex objects */

Complex operator /(const Complex& c1, const Complex& c2){

	Complex conj = !c2;

	double c2Norm2 = c2.norm2();

	return (c1 * conj) / c2Norm2;
}


void Complex::operator +=(const Complex& c){

	a += c.a;
	b += c.b;
}


void Complex::operator -=(const Complex& c){

	a -= c.a;
	b -= c.b;
}


void Complex::operator *=(const Complex& c){

	a = a * c.a - b * c.b;
	b = a * c.b + b * c.a;
}


void Complex::operator /=(const Complex& c){

	*this = (*this) / c;
}


Complex pow(const Complex& c, double f){

	double rho = pow(c.getRho(), f);
	double theta = f * c.getTheta();

	return Complex(rho * cos(theta), rho * sin(theta));
}


/* with scalars */

Complex operator /(const Complex& c1, double c){

	assert(not comparef(c, .0));

	return Complex(c1.a / c, c1.b / c);
}

Complex operator /(double c, const Complex& c1){

	Complex c2(c, .0);
	
	return (c2 / c1);
}


void Complex::operator /=(double c){

	assert(not comparef(c, .0));

	a /= c;
	b /= c;
}


/* other */

std::ostream& operator <<(std::ostream& os, const Complex& c){

	if (c.isReal())			{ os << c.a; }
	else if (c.isImaginary())	{ os << c.b << "i"; }
	else				{ os << c.a << (c.b > 0? "+": "") << c.b << "i"; }

	return os;
}






