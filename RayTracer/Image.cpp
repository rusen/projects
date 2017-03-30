#include "Image.h"
#include <fstream>

using namespace std;

Image::Image() {}

Image::Image(int width, int height) {

	nx = width;
	ny = height;
	
	raster = new rgb*[nx];
	
	for (int i=0;i<nx;i++)
		raster[i] = new rgb[ny];
}

Image::Image(int width, int height, rgb background) {

	nx=width;
	ny=height;
	
	raster = new rgb*[nx];
	for (int i=0;i<nx;i++){
		raster[i] = new rgb[ny];
		for (int j=0; j<ny;j++)
			raster[i][j] = background;
	}
}

bool Image::set(int x,int y, const rgb& color) {
	if (0>x || x>nx) return false;
	if (0>y || y>ny) return false;
	
	raster[x][y] = color;

}

void Image::gammaCorrect(float gamma) {
	rgb temp;
	float power = 1.0/gamma;
	for(int i= 0; i<nx;i++)
		for(int j=0; j<ny;j++) {
		temp = raster[i][j];
		raster[i][j] = rgb(pow(temp.r(),power),pow(temp.g(),power),pow(temp.b(),power));
		}

}

void Image::writePPM(fstream& out){
	out<< "P6\n";
	out<<nx<<' '<<ny<<'\n';
	out<<"255\n";
	
	int i,j;
	unsigned int ired, igreen,iblue;
	unsigned char red,green,blue;
	
	for (i = ny-1; i>=0; i--)
		for(j=0; j<nx; j++) {
			
			ired = (unsigned int) (256*raster[j][i].r());
			igreen = (unsigned int) (256*raster[j][i].g());
			iblue = (unsigned int) (256*raster[j][i].b());
			if (ired>255) ired = 255;
			if (igreen>255) igreen = 255;
			if (iblue>255) iblue = 255;
			red = (unsigned char) (ired);
			green = (unsigned char) (igreen);
			blue = (unsigned char) (iblue);
			
			out.put(red);
			out.put(green);
			out.put(blue);
		
		}
		


		
}

int Image::getWidth() {return nx;}
int Image::getHeight() {return ny;}
