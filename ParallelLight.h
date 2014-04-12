#ifndef PARALLEL_LIGHT_H
#define PARALLEL_LIGHT_H

#include "DirectionalLight.h"

class ParallelLight : public DirectionalLight {
   public:
      ParallelLight(
      	String name, 
      	const Color color, 
      	const Vector location,
      	const Vector direction, 
      	const double intensity);
      virtual const Vector getLightRay(const Vector *hitPoint) const;
};

#endif
