#include "Plane.h"

Plane::Plane(String name, const Material material) : Shape(name, material) {}

Plane::Plane(
	String name,  
	const Material material, 
	const Vector orientation, 
	const Vector location) : 
		Shape(name, material), 
		location(location), 
		orientation(orientation.normalize()) {}

const Vector Plane::getOrientation() const {return orientation;}
 
void Plane::setOrientation(const Vector orientation) {this->orientation = orientation.normalize();}

const Vector Plane::getLocation() const {return location;}
 
void Plane::setLocation(const Vector location) {this->location = location;}
      
inline HitData *Plane::hit(const Vector *ray, const Vector *pixelPosition) const {
   double hit(*ray * orientation);
   if (hit == 0) return NULL;
   double t(((orientation * location) - (orientation * *pixelPosition)) / hit);
   if (t <= MAGIC_NUMBER) return NULL;
   Vector hitPoint(*pixelPosition + (*ray * t));
   double distance((hitPoint - *pixelPosition).magnitude());
   Vector reflectionRay((*ray - (orientation * 2 * (orientation * *ray))).normalize());
   HitData *hitData = new HitData();
   if (orientation * (*ray * -1) < 0) hitData->surfaceNormal = *ray * -1;
   else hitData->surfaceNormal = orientation;
   hitData->pixelPosition = *pixelPosition;
   hitData->reflectionRay = reflectionRay;
   hitData->hitPoint = hitPoint;
   hitData->hitObject = this;
   hitData->distance = distance;
   hitData->viewRay = *ray;
   return hitData;
}
