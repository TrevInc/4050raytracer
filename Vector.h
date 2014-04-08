#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

class Vector {
   public:
      double x; 
      double y; 
      double z;
      Vector();
      Vector(const double x, const double y, const double z);
      Vector operator+(const Vector &v1) const;
      Vector operator-(const Vector &v1) const;
      Vector operator-() const;
      Vector operator*(const double &scalar) const;
      Vector operator/(const double &scalar) const;
      const double operator*(const Vector &v1) const;
      Vector operator%(const Vector &v1) const;
      Vector normalize() const;
      const double magnitude() const;
};

#endif
