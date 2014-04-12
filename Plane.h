#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

#define MAGIC_NUMBER 0.0000001

class Plane : public Shape {
   protected:
      Vector location;
      Vector orientation;
   public:
   	Plane(String name, const Material material);
      Plane(
      	String name, 
      	const Material material, 
      	const Vector orientation, 
      	const Vector location);
      const Vector getOrientation() const;
      void setOrientation(const Vector orientation);
      const Vector getLocation() const;
      void setLocation(const Vector location);
      virtual HitData *hit(
      	const Vector *ray, 
      	const Vector *pixelPosition) const;
};

#endif
