#include "Mandelbrot.h"
#include "Buddhabrot.h"
#include "MandelbrotMath.h"
#include "Palette.h"
#include "JPGTools.h"

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <cassert>

const unsigned int K = 5;

/* width height iter_red iter_green iter_blue */


int main(int argc, char** argv){
	
	assert(argc == (K + 1));
		
	int width =  atoi(argv[1]);
	int height = atoi(argv[2]);
	int iter_r = atoi(argv[3]);
	int iter_g = atoi(argv[4]);
	int iter_b = atoi(argv[5]);


	std::vector<unsigned int> passBuffer;

	std::string addr = "renderings/buddha.jpg";
	std::string addr_r = "renderings/temp/buddha_r.jpg";
	std::string addr_g = "renderings/temp/buddha_g.jpg";
	std::string addr_b = "renderings/temp/buddha_b.jpg";

	double deltax = 0.5;
	Complex center(-1.2, .0);

	Buddhabrot buddhabrot(width, height, deltax);

	buddhabrot.setIterations(iter_r);
	buddhabrot.render(center, passBuffer);
	buddhabrot.saveJPG(addr_r, passBuffer);

	buddhabrot.setIterations(iter_g);
	buddhabrot.render(center, passBuffer);
	buddhabrot.saveJPG(addr_g, passBuffer);

	buddhabrot.setIterations(iter_b);
	buddhabrot.render(center, passBuffer);
	buddhabrot.saveJPG(addr_b, passBuffer);

	combine(addr, addr_r, addr_g, addr_b);

	return 0;
}
