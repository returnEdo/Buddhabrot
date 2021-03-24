#pragma once

#include "MandelbrotMath.h"
#include "MandelbrotConstants.h"
#include "Palette.h"

#include <vector>


class Mandelbrot{

	private:

	/* data */
	int width; 						// # of pixels
	int height;

	double deltax;						// width in world coordinates
	double deltay;

	double step;

	std::vector<double>		iterHistogram;		// histogram
	std::vector<unsigned int> 	iterPixel;		// iterations for each pixel

	unsigned int iterMax = MAX_ITER;
	double counter = .0;

	/* methods */
	unsigned int findIterations(Complex& z0, Complex& c,
				    void (*map)(Complex&, Complex&)) const;
	Vector findColor(unsigned int iter, const Palette& palette) const;

	public:

	Mandelbrot(int width_, int height_, double samplex_);
	
	/* setters */

	inline void setIterations(unsigned int iterMax_)	{ iterMax = iterMax_; }

	void render(const Complex& center, Complex& z0,
		    void (*map)(Complex&, Complex&), const Palette& palette, std::vector<Vector>& colors);
};

