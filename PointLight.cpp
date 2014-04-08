#include "PointLight.h"

PointLight::PointLight(
	const String name, 
	const Vector location, 
	const Color color, 
	const double intensity) :
		Light(name, color, location, intensity) {}
		
PointLight::PointLight(
	const String name, 
	const Vector location, 
	const enum Colors color, 
	const double intensity) :
		Light(name, color, location, intensity) {}
		
		
