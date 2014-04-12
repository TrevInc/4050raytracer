#ifndef SPHERE_H
#define SPHERE_H

#include "Vector.h"
#include "Shape.h"

class Sphere : public Shape {
   private:
      const double radius;
      const Vector center;
   public:
      Sphere(
      	String name, 
      	const Material material, 
      	const double radius, 
      	const Vector center);
      virtual HitData *hit(
      	const Vector *ray, 
      	const Vector *pixelPosition) const;
};

#endif
