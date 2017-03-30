#ifndef _SCENE_H_
#define _SCENE_H_


#include <vector>
#include <iostream>
#include "Vector3.h"
#include "Shape.h"	
#include "Light.h"
#include "Camera.h"
#include "Ray.h"
#include "rgb.h"
#include "Image.h"
#include <fstream>
#include "string.h"
#include "stdlib.h"

class Scene {
	public:
	
	Scene();
	Scene(const vector<Shape*> &s1, const vector<Light*> &l1, const Camera &c1, const Image &img, int cn, const Vector3& _ambientl, const Vector3& _backgroundcol, float _tmin, char* _name );
	
	void push_shape(Shape* s1);
	void push_light(Light* l1);
	void push_cam(Camera &c1);
	void set_image(Image &img);
	void Render();
	Vector3 sendRay(Ray& r ,int count); 
	
	vector<Shape*> shapes;
	vector<Light*> lights;
	Camera cam;
	Image im;
	int reflectcount;
	Vector3 ambientl;
	Vector3 backgroundcol;
	float tmin;
	char* name;
	
};


#endif
