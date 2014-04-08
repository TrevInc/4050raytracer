#include "Sphere.h"

Sphere::Sphere(
	String name,
	const Material material, 
	const double radius, 
	const Vector center) : 
		Shape(name, material), 
		radius(radius), 
		center(center) {}

Sphere::Sphere(
	String name,  
	const enum Materials material, 
	const double radius, 
	const Vector center) : 
		Shape(name, material), 
		radius(radius), 
		center(center) {}

inline HitData *Sphere::hit(const Vector *ray, const Vector *pixelPosition) const {
    double t = *ray * (center - *pixelPosition);
    if (t < 0) return NULL;
    double d = (*pixelPosition + (*ray * t) - center).magnitude();
    if (d > radius) return NULL;
    Vector hitPoint = *pixelPosition + (*ray * (t - sqrt(pow(radius, 2) - pow(d, 2))));
    Vector surfaceNormal = (hitPoint - center).normalize();
    HitData *hitData = new HitData();
    hitData->hitPoint = hitPoint;
    hitData->pixelPosition = *pixelPosition;
    hitData->viewRay = *ray;
    hitData->surfaceNormal = surfaceNormal;
    hitData->reflectionRay = (*ray - (surfaceNormal * 2 * (surfaceNormal * *ray))).normalize();
    hitData->hitObject = this;
    hitData->distance = (hitPoint - *pixelPosition).magnitude();
    return hitData;
}
