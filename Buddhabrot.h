#pragma once

#include <vector>
#include <string>

#include "MandelbrotMath.h"
#include "MandelbrotConstants.h"


void combine(const std::string& addr,
	     const std::string& addr_r,
	     const std::string& addr_g,
	     const std::string& addr_b);


class Buddhabrot{

	private:
	
	int width;
	int height;

	double deltax;
	double deltay;

	double step;

	unsigned int iterMax = MAX_ITER;

	bool findOrbit(const Complex& z0, const Complex& c, std::vector<Complex>& orbitBuffer) const;
	bool isVisible(const Complex& z, const Complex& center) const;
	int getIndex(const Complex& z, const Complex& center) const;

	public:

	Buddhabrot(int width_, int height_, double deltax_);

	/* setters */
	inline void setIterations(unsigned int iterMax_)	{ iterMax = iterMax_; }


	void render(const Complex& center, std::vector<unsigned int>& passBuffer);

	void saveJPG(const std::string& addr, const std::vector<unsigned int>& passBuffer) const;
};
