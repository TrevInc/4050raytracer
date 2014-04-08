#include "Vector.h"

Vector::Vector() : x(), y(), z() {}

Vector::Vector(const double x, const double y, const double z) :  
	x(x), 
	y(y), 
	z(z) {}

Vector Vector::operator+(const Vector& v1) const {
    return Vector(x + v1.x, y + v1.y, z + v1.z);
}

Vector Vector::operator-(const Vector& v1) const {
    return Vector(x - v1.x, y - v1.y, z - v1.z);
}

Vector Vector::operator-() const {
    return Vector(-x, -y, -z);
}

Vector Vector::operator*(const double& scalar) const {
    return Vector(x * scalar, y * scalar, z * scalar);
}

Vector Vector::operator/(const double& scalar) const {
    return Vector(x / scalar, y / scalar, z / scalar);
}

const double Vector::operator*(const Vector& v1) const {
    return (x * v1.x) + (y * v1.y) + (z * v1.z);
}

Vector Vector::operator%(const Vector& v1) const {
    return Vector(y * v1.z - z * v1.y, z * v1.x - x * v1.z, x * v1.y - y * v1.x);
}

Vector Vector::normalize() const {
    double magnitude = this->magnitude();
    return Vector(x / magnitude, y / magnitude, z / magnitude);
}

const double Vector::magnitude() const {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}
