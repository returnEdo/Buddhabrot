#include "Mandelbrot.h"
#include "MandelbrotMath.h"
#include "Palette.h"
#include "JPGTools.h"

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

void MandelbrotSet(Complex& zn, Complex& c){

	zn = pow(zn, 2.0) + c;
}


void BurningShipSet(Complex& zn, Complex& c){

	Complex zz(abs(zn.a), abs(zn.b));

	zn = pow(zz, 2) + c;
}

int main(){
	
	std::vector<Vector> clrs = {Vector(20.0f), Vector(220.0f)};

	Palette palette(clrs);
	
	std::string addr = "renderings/mbrt.jpg";

	int width = 1920;
	int height = 1080;
	
	double deltax = .00005;

	Mandelbrot mandelbrot(width, height, deltax);
	mandelbrot.setIterations(1000);

	std::vector<Vector> colors;
	Complex center(-1.7686, .0008976);
	Complex z0;

	mandelbrot.render(center, z0, MandelbrotSet, palette, colors);

	saveJpg(addr, width, height, colors);

	return 0;
}
