#include "ParallelLight.h"

ParallelLight::ParallelLight(
	String name, 
	const enum Colors color,
	const Vector location,
	const Vector direction, 
	const double intensity) :
		DirectionalLight(name, color, location, direction, intensity) {}
		
ParallelLight::ParallelLight(
	String name, 
	const Color color,
	const Vector location,
	const Vector direction, 
	const double intensity) :
		DirectionalLight(name, color, location, direction, intensity) {}

const Vector ParallelLight::getLightRay(const Vector *hitPoint) const {return direction;}

