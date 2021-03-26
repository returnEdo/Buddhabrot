#include "Buddhabrot.h"

#include <cmath>
#include <cassert>

#include "JPGTools.h"


Buddhabrot::Buddhabrot(int width_, int height_, double deltax_):
	width(width_),
	height(height_),
	deltax(deltax_) {

	double alpha = static_cast<double>(width) / static_cast<double>(height);

	deltay = deltax / alpha;

	step = deltax / static_cast<double>(width);
}


bool Buddhabrot::findOrbit(const Complex& z0, const Complex& c, std::vector<Complex>& orbitBuffer) const{
	/* follows also the unstable orbits */

	Complex zn = z0;

	bool stable = true;

	for (int i = 1; i <= iterMax; i++){
		
		zn = pow(zn, 2.0) + c;

		orbitBuffer.push_back(zn);
		
		if (norm2(zn) >= 2.0){
			
			stable = false;
		}
	}
	return stable;
}


bool Buddhabrot::isVisible(const Complex& z, const Complex& topLeft) const{
	
	double ar = z.a - topLeft.a;
	double br = -z.b + topLeft.b;
	
	return ((ar >= 0 and ar <= deltax) and
		(br >= 0 and br <= deltay));
}


int Buddhabrot::getIndex(const Complex& z, const Complex& topLeft) const{
	
	Complex zr = z - topLeft;

	zr.b *= -1.0;
	
	/* indices */
	int re = static_cast<int>(zr.a / step);
	int im = static_cast<int>(zr.b / step);

	if (fmod(zr.a, step) > .5)	{ re++; }
	if (fmod(zr.b, step) > .5)	{ im++; }

	return (re + width * im);
}


void Buddhabrot::render(const Complex& center, std::vector<unsigned int>& passBuffer){
	/* pass buffer will be filled with the number of passes */

	passBuffer = std::vector<unsigned int>(width * height, 0);

	Complex z0;
	Complex topLeft(center.a - deltax / 2.0,
			center.b + deltay / 2.0);

	double dl = step / 3.0;
			
	for (int j = 0; j < height; j++){

		for (int i = 0; i < width; i++){

			Complex c(center.a - deltax / 2.0 + step * i + rand_d(-dl, dl),
				  center.b + deltay / 2.0 - step * j + rand_d(-dl, dl));
			
			std::vector<Complex> orbitBuffer;

			bool stable = findOrbit(z0, c, orbitBuffer);

			if (stable){
				/* we are interested only in unstable orbits */
				
				for (const Complex& z: orbitBuffer){
					
					if (isVisible(z, topLeft)){
						/* if the point is inside the viewport */

						passBuffer[getIndex(z, topLeft)] += 1.0;		// update the counter
					}
				}
			}
		}
	}
}


void Buddhabrot::saveJPG(const std::string& addr, const std::vector<unsigned int>& passBuffer) const{

	unsigned int max = 0;

	for (unsigned int uint: passBuffer){
		
		if (uint > max)	{ max = uint; }
	}
	
	float maxf = static_cast<float>(max);

	std::vector<Vector> colors;

	for (int i = 0; i < passBuffer.size(); i++){
		
		colors.push_back(Vector(255.0f * static_cast<float>(passBuffer[i]) / maxf));
	}

	saveJpg(addr, width, height, colors);
}



void combine(const std::string& addr,
	     const std::string& addr_r,
	     const std::string& addr_g,
	     const std::string& addr_b){

	std::vector<Vector> data;
	std::vector<Vector> data_r;
	std::vector<Vector> data_g;
	std::vector<Vector> data_b;

	int width_r, width_g, width_b;
	int height_r, height_g, height_b;

	readJpg(addr_r, &width_r, &height_r, data_r);
	readJpg(addr_g, &width_g, &height_g, data_g);
	readJpg(addr_b, &width_b, &height_b, data_b);

	assert((width_r == width_g) and (width_g == width_b));
	assert((height_r == height_g) and (height_g == height_b));

	float gamma = .5f;

	for (int j = 0; j < height_r; j++){
		
		for (int i = 0; i < width_r; i++){
			
			int k = j * width_r + i;

			data.push_back({pow(data_r[k].x, gamma), 
					pow(data_g[k].y, gamma),
					pow(data_b[k].z, gamma)});
			data[k] *= 255.0f;
		}
	}

	saveJpg(addr, width_r, height_r, data);
}
