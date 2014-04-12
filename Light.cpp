#include "Light.h"

Light::Light(
	String name, 
	const Color color, 
	const Vector location, 
	const double intensity) : 
		ColoredObject(name, color), 
		location(location), 
		intensity(intensity) {}

const Vector Light::getLocation() const {return location;}

void Light::setLocation(const Vector location) {this->location = location;}

inline const double Light::getIntensity(const Vector *hitPoint) const {return intensity;}

void Light::setIntensity(const double intensity) {this->intensity = intensity;}

inline const Vector Light::getLightRay(const Vector *hitPoint) const {return (*hitPoint - location).normalize();}
