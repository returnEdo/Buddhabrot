#pragma once

#include <vector>

#include "Vector.h"


class Palette{

	private:

	std::vector<Vector> colors;

	int N;

	public:

	Palette(const std::vector<Vector>& colors_);

	Vector getColorAt(double t) const;
};
