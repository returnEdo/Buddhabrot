#pragma once

#include <limits>

#include "Vector.h"

const double	ZERO_F = 10.0 * std::numeric_limits<double>::min();

bool comparef(double a, double b);

Vector lerp(float t, const Vector& a, const Vector& b);
Vector lerp(double t, const Vector& a, const Vector& b);

double rand_d(double a, double b);
