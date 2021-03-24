#pragma once

#include <cmath>
#include <iostream>

#include "MathMisc.h"

class Complex{

	public:

	double a;					// real part
	double b;					// imaginary part

	public:

	Complex(void);
	Complex(double a_, double b_);
	Complex(const Complex& other);
	
	/* getters */

	inline double getRho(void)	const	{ return sqrt(norm2()); }
	inline double getTheta(void) 	const	{ return atan2(b, a); }	

	inline double norm(void)	const 	{ return getRho(); }
	inline double norm2(void)	const	{ return (a * a + b * b); }

	inline bool isReal(void)	const 	{ return comparef(b, .0); }
	inline bool isImaginary(void)	const	{ return comparef(a, .0); }
	inline bool isStable(void)	const	{ return (a < .0f); }

	inline friend double getRho(const Complex& c)		{ return c.getRho(); }
	inline friend double getTheta(const Complex& c) 	{ return c.getTheta(); }	

	inline friend double norm(const Complex& c)		{ return c.getRho(); }
	inline friend double norm2(const Complex& c)		{ return c.norm2(); }

	inline friend bool isReal(const Complex& c)		{ return c.isReal(); }
	inline friend bool isImaginary(const Complex& c)	{ return c.isImaginary(); }
	inline friend bool isStable(const Complex& c)		{ return c.isStable(); }

	/* operations */

	void operator =(const Complex& c);
	inline friend bool operator ==(const Complex& c1, const Complex& c2)		{ return (comparef(c1.a, c2.a) and comparef(c1.b, c2.b)); }

	/* with Complex objects */
	inline friend Complex operator +(const Complex& c1, const Complex& c2)		{ return Complex(c1.a + c2.a, c1.b + c2.b); }
	inline friend Complex operator -(const Complex& c1, const Complex& c2)		{ return Complex(c1.a - c2.a, c1.b - c2.b); }
	inline friend Complex operator *(const Complex& c1, const Complex& c2)		{ return Complex(c1.a * c2.a - c1.b * c2.b, c1.a * c2.b + c1.b * c2.a); }
	friend Complex operator /(const Complex& c1, const Complex& c2);

	void operator +=(const Complex& c);
	void operator -=(const Complex& c);
	void operator *=(const Complex& c);
	void operator /=(const Complex& c);

	friend Complex pow(const Complex& c, double f);
	inline friend Complex operator !(const Complex& c)			{ return Complex(c.a, -c.b); }
	
	/* with scalars */
	/* scalrs om the left */
	inline friend Complex operator +(const Complex& c1, double c)		{ return Complex(c1.a + c, c1.b); }
	inline friend Complex operator -(const Complex& c1, double c)		{ return Complex(c1.a - c, c1.b); }
	inline friend Complex operator *(const Complex& c1, double c)		{ return Complex(c1.a * c, c1.b * c); }
	friend Complex operator /(const Complex& c1, double c);

	inline void operator +=(double c)					{ a += c; }
	inline void operator -=(double c)					{ a -= c; }
	inline void operator *=(double c)					{ a *= c; b *= c; }
	void operator /=(double c);
	
	/* scalars on the right */
	inline friend Complex operator +(double c, const Complex& c1)		{ return (c1 + c); }
	inline friend Complex operator -(double c, const Complex& c1)		{ return (c1 - c); }
	inline friend Complex operator *(double c, const Complex& c1)		{ return (c1 * c); }
	friend Complex operator /(double c, const Complex& c1);

	/* other */
	
	friend std::ostream& operator <<(std::ostream& os, const Complex& c);

};
