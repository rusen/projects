#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_ 1

#include "Shape.h"
#include "Vector3.h"
#include "rgb.h"
#include "Ray.h"

class Triangle : public Shape {

public:
	Triangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, const struct Material& _material);
	bool intersect(const Ray& r1, float tmin, HitRecord& record) const;
	bool shadowHit(const Ray& r1, float tmin) const ;
	
	Vector3 p0;
	Vector3 p1;
	Vector3 p2;
	
	struct Material material;

};

#endif
