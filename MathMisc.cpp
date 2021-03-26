#include "MathMisc.h"

#include <cstdlib>

bool comparef(double a, double b){

	double c = a - b;
	c *= (c > .0? 1.0: -1.0);

	return c <= ZERO_F;
}
Vector lerp(float t, const Vector& a, const Vector& b){

	return a * t + b * (1.0 - t);
}

Vector lerp(double t, const Vector& a, const Vector& b){

	return lerp((float)(t), a, b);
}


double rand_d(double a, double b){

	return (static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (b - a) + a);
}

