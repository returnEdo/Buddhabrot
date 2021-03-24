#include "Palette.h"

#include <cmath>

#include "MandelbrotMath.h"

Palette::Palette(const std::vector<Vector>& colors_):
	colors(colors_),
	N(colors.size())	{}



Vector Palette::getColorAt(double t) const{
	
	t *= (N - 1.0);

	int M = static_cast<int>(ceil(t));
	int m = static_cast<int>(floor(t));

	double f = t - static_cast<double>(m);

	return lerp(f, colors[m], colors[M]);
}
