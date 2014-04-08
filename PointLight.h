#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"

class PointLight : public Light {
   public:
   	PointLight(
      	const String name, 
      	const Vector location, 
      	const Color color, 
      	const double intensity);
      PointLight(
      	const String name, 
      	const Vector location, 
      	const enum Colors color, 
      	const double intensity);
};

#endif
