#include "DirectionalLight.h"
	
DirectionalLight::DirectionalLight(
   String name, 
   const Color color, 
   const Vector location, 
   const Vector direction, 
   const double intensity) :
   	Light(name, color, location, intensity),
   	direction(direction) {}
      
inline const Vector *DirectionalLight::getDirection() const {return &direction;}
      
void DirectionalLight::setDirection(const Vector direction) {this->direction = direction;}
