#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"

class DirectionalLight : public Light {
   protected:
      Vector direction;
   public:
      DirectionalLight(
      	String name, 
      	const Color color, 
      	const Vector location, 
      	const Vector direction, 
      	const double intensity);
      DirectionalLight(
      	String name, 
      	const enum Colors color, 
      	const Vector location, 
      	const Vector direction, 
      	const double intensity);
      const Vector *getDirection() const;
      void setDirection(const Vector direction);
};

#endif
