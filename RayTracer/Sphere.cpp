#include "Sphere.h"

Sphere::Sphere(const Vector3& _center, float _radius, const struct Material& _material)
	: center(_center), radius(_radius), material(_material) {}
	
bool Sphere::intersect(const Ray& r, float tmin, HitRecord& h1) const {
	
	Vector3 temp = r.origin() - center;
	double a = dot(r.direction(), r.direction());
	double b = 2*dot(r.direction(), temp);
	double c = dot(temp,temp) - radius*radius;

	double discriminant = b*b - 4*a*c;
	
	if (discriminant > 0) {
	discriminant = sqrt(discriminant);
	double t = (-b - discriminant) / (2*a);
	
	if (t<tmin) {
		t = (-b + discriminant) / (2*a);
	}
	if ((t < 1)) {
		return false;
	}
	
	h1.t = t;
	h1.normal = unitVector(r.origin() + t*r.direction() - center);
	h1.point = r.origin() + t*r.direction();
	h1.material = material;
	return true;
	
	
	}
	return false;
}
	
bool Sphere :: shadowHit(const Ray& r, float tmin) const{
	Vector3 temp = r.origin() - center;
	double a = dot(r.direction(),r.direction());
	double b = 2*dot(r.direction(), temp);
	double c = dot(temp,temp) - radius*radius;
	
	double discriminant = b*b - 4*a*c;
	
	if (discriminant>0) {
	
		discriminant = sqrt(discriminant);
		double t = (-b -discriminant) / (2*a);
		if (t<tmin)
			t = (-b + discriminant) / (2*a);
		if (t<tmin)
			return false;
	
		return true;
	}
	return false;
	}


