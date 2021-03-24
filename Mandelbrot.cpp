#include "Mandelbrot.h"

#include <limits>

Mandelbrot::Mandelbrot(int width_, int height_, double deltax_):
	width(width_),
	height(height_),
	deltax(deltax_){
	
	double alpha = static_cast<double>(width) / static_cast<double>(height);

	deltay = deltax / alpha;

	step = deltax / (static_cast<double>(width) - 1.0);

	iterHistogram = std::vector<double>(iterMax, .0);
	iterPixel = std::vector<unsigned int>(width * height, iterMax);
}


unsigned int Mandelbrot::findIterations(Complex& z0, Complex& c,
					void (*map)(Complex&, Complex&)) const{

	Complex zn = z0;

	double INST_THRESH_2 = INSTABILITY_THRESHOLD * INSTABILITY_THRESHOLD;

	for (unsigned int i = 1; i < iterMax; i++){
		
		map(zn, c);
		
		/* stability of the orbit test */
		if (norm2(zn) >= INST_THRESH_2){

			return i;
		}

	}

	return iterMax;
}


Vector Mandelbrot::findColor(unsigned int iter, const Palette& palette) const{

	if (iter == iterMax)	{ return Vector(); }
	else{

		double t = 0.0;

		for (int i = 1; i <= iter; i++){

			t += iterHistogram[i - 1] / counter;
		}
		
		return palette.getColorAt(t);
	}
}


void Mandelbrot::render(const Complex& center, Complex& z0,
			void (*map)(Complex&, Complex&), const Palette& palette, std::vector<Vector>& colors){

	/* find the iterations for each pixel */
	for (int j = 0; j < height; j++){

		for (int i = 0; i < width; i++){
		
			Complex c(center.a - deltax / 2.0 + i * step,
				  center.b + deltay / 2.0f - j * step);

			unsigned int iter = findIterations(z0, c, map);

			iterHistogram[iter - 1] += 1.0;
			iterPixel[i + j * width] = iter;
		}
	}

	/* dimension of the histogram */
	for (int i = 0; i < iterMax; i++)	{ counter += iterHistogram[i]; }

	/* sets the color */
	for (int j = 0; j < height; j++){

		for (int i = 0; i < width; i++){
	
			colors.push_back(findColor(iterPixel[i + j * width], palette));
		}	
	}
}
