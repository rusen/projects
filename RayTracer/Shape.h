#ifndef _SHAPE_H_
#define _SHAPE_H_ 1

#include "Ray.h"
#include "Vector3.h"
#include "rgb.h"

class Ray;
class rgb;

struct Material{
	Vector3 diffuse;
	Vector3 specular;
	Vector3 ambient;
	Vector3 reflectance;
	float specexp;
};

struct HitRecord {
	float t;
	Vector3 normal;
	struct Material material;
	Vector3 point;
};

class Shape{
	public:
	virtual bool intersect(const Ray& r1, float tmin, HitRecord &h1) const=0;
	virtual bool shadowHit(const Ray& r1 , float tmin) const = 0;
};


#endif
