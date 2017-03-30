#include <math.h>
//#include "Vector3.h"

template <class T>
Vector3<T>::Vector3 () {
}

template <class T>    
Vector3<T>::Vector3(T x, T y, T z) {
	_x = x;
	_y = y;
	_z = z;
}

template <class T>    
Vector3<T>::Vector3(const Vector3& v) {
	_x = v._x; 
	_y = v._y; 
	_z = v._z;
}

template <class T>
Vector3<T>& Vector3<T>::operator=(const Vector3<T>& v) {
		if (this != &v){
		_x = v._x;
		_y = v._y;
		_z = v._z;
		}
		return *this;
}


template <class T>
T Vector3<T>::x() const {
	return _x;
}
template <class T>
T Vector3<T>::y() const {
	return _y;
}
template <class T>
T Vector3<T>::z() const {
	return _z;
}


template <class T>
void Vector3<T>::setX(T x){
	_x = x;
}

template <class T>
void Vector3<T>::setY(T y){
	_y = y;
}

template <class T>
void Vector3<T>::setZ(T z){
	_z = z;
}

template <class T>
T Vector3<T>::dot(const Vector3& vec) const {

	return _x * vec._x + _y * vec._y + _z * vec._z;

}

template <class T>
Vector3<T> Vector3<T>::cross(const Vector3&  vec) const {
	return Vector3(_y * vec._z - _z * vec._y,
			_z * vec._x - _x * vec._z,
			_x * vec._y - _y * vec._x);
}

template <class T>
void Vector3<T>::normalize() {	
	T magnitude = sqrtf(_x * _x + _y * _y + _z * _z);
	_x /= magnitude;
	_y /= magnitude;
	_z /= magnitude;
}

template <class T>
T Vector3<T>::length() const {
	return sqrtf(_x * _x + _y * _y + _z * _z);
}

template <class T>    
Vector3<T> Vector3<T>::operator+(const Vector3& vec) const {
	return Vector3(_x + vec._x, _y + vec._y, _z + vec._z);	
}
template <class T>
Vector3<T> Vector3<T>::operator-(const Vector3& vec) const{
	return Vector3(_x - vec._x, _y - vec._y, _z - vec._z);	
}

template <class T>
Vector3<T> Vector3<T>::operator*(T num) const{
	return Vector3(num*_x,num*_y,num*_z);
}

template <class T>
Vector3<T>& Vector3<T>::operator+=(const Vector3& v){
	Vector3& vnew;
	vnew._x = v._x + _x;
	vnew._y = v._y + _y;
	vnew._z = v._z + _z; 
	return vnew;
}

template <class T>
Vector3<T>& Vector3<T>::operator-=(const Vector3& v) {
	Vector3& vnew;
	vnew._x = v._x - _x;
	vnew._y = v._y - _y;
	vnew._z = v._z - _z; 
	return vnew;
}
    
template <class T>
Vector3<T>& Vector3<T>::operator*=(T num) {
	Vector3& vnew;
	vnew._x = num*_x;
	vnew._y = num*_y;
	vnew._z = num*_z; 
	return vnew;
}

template<class T>
Vector3<T> operator*(T num, const Vector3<T>&vec){
	
	return Vector3<T>(num*vec.x(),num*vec.y(),num*vec.z());

}




