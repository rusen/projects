#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Vector3.h"
#include "rgb.h"

class Light{
	
	public:
	
	Light(const Vector3& _center,const Vector3& _color) : center(_center), color(_color) {}
	Vector3 center;
	Vector3 color;
	
};	


#endif
