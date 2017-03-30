#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <cmath>
#include <string>
#include <fstream>
#include "rgb.h"

using namespace std;

class Image {
public:

	Image();
	Image(int width, int height);
	Image(int width, int height, rgb background);
	int getWidth();
	int getHeight();
	bool set(int x, int y, const rgb& color);
	void gammaCorrect(float gamma);
	void writePPM(fstream& out);
	
private:
	
	rgb **raster;
	int nx;
	int ny;

};

#endif
