template<class T>
class Vector3
{
public:
    // Constructors
    Vector3();
    Vector3(T, T, T);
    Vector3(const Vector3&);

    // Assignment operator (can be chained)
    Vector3& operator=(const Vector3&);

    // Accessors
    T x() const;
    T y() const;
    T z() const;

    void setX(T);
    void setY(T);
    void setZ(T);

    // Misc. operations
    T dot(const Vector3&) const;
    Vector3 cross(const Vector3&) const;

    void normalize();
    T length() const;


    // Arithmetic
    Vector3 operator+(const Vector3&) const;
    Vector3 operator-(const Vector3&) const;
    Vector3 operator*(T) const;

    Vector3& operator+=(const Vector3&);
    Vector3& operator-=(const Vector3&);
    Vector3& operator*=(T);

private:
    T _x, _y, _z;
};

template<class T>
Vector3<T> operator*(T, const Vector3<T>&);  // unfortunately this needs to be outside the class */

void v(){

}

