#ifndef _PARSER_H_
#define _PARSER_H_

#include <fstream>
#include <iostream>
#include <string.h>
#include "Scene.h"
#include "Triangle.h"
#include "Shape.h"
#include "Vector3.h"
#include "Sphere.h"
#include "Light.h"
#include "Camera.h"
#include "Image.h"

class Parser{
	public:
	Parser();
	void Parsefile(const char * filename);
	Scene ConstructScene(char*);
	
	vector<struct Material> materials;
	vector<Shape*> shapes;
	vector<Light*> lights;
	Camera cam;
	Image im;
	Vector3 ambient;
	Vector3 back;
	float tmin;
	float tmax;
	float p;
	int width;
	int height;
	int reflectc;
	


};

#endif
