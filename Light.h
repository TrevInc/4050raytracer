#ifndef LIGHT_H
#define LIGHT_H

#include "ColoredObject.h"
#include "Vector.h"

class Light : public ColoredObject {
   protected:
      Vector location;
      double intensity;
   public:
      Light(
      	String name, 
      	const Color color, 
      	const Vector location, 
      	const double intensity);
      Light(
      	String name, 
      	const enum Colors color, 
      	const Vector location, 
      	const double intensity);
      void setLocation(const Vector location);
      const Vector getLocation() const;
      void setIntensity(const double intensity);
      virtual const double getIntensity(const Vector *hitPoint) const;
      virtual const Vector getLightRay(const Vector *hitPoint) const;
};

#endif
