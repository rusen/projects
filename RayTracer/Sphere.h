
#ifndef _SPHERE_H_
#define _SPHERE_H_ 1

#include "Shape.h"
#include "Vector3.h"
#include "Ray.h"
#include "rgb.h"


class Sphere : public Shape {

public:
	Sphere(const Vector3& _center, float _radius, const struct Material& _material);
	bool intersect(const Ray& r1, float tmin,HitRecord& h1) const;
	bool shadowHit(const Ray& r1, float tmin) const;
	
	Vector3 center;
	float radius;
	struct Material material;
	
};

#endif
