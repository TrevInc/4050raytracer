#include "PointLight.h"

PointLight::PointLight(
	const String name, 
	const Vector location, 
	const Color color, 
	const double intensity) :
		Light(name, color, location, intensity) {}

		
		
