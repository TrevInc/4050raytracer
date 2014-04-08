#include "Triangle.h"

Triangle::Triangle(
	String name,  
	const enum Materials material, 
	const Vector p0, 
	const Vector p1, 
	const Vector p2) : 
		Plane(name, material),
		p0(p0), 
		p1(p1), 
		p2(p2), 
		edge0(p1 - p0), 
		edge1(p2 - p1), 
		edge2(p0 - p2),
		phongShading(false),
		textureMap(false) {
			this->location = p0;
			this->orientation = (edge0 % edge1).normalize();
		}
		
Triangle::Triangle(
	String name,  
	const Material material, 
	const Vector p0, 
	const Vector p1, 
	const Vector p2) :
		Plane(name, material),
		p0(p0), 
		p1(p1), 
		p2(p2),
		edge0(p1 - p0), 
		edge1(p2 - p1), 
		edge2(p0 - p2),
		phongShading(false),
		textureMap(false) {
			this->location = p0;
			this->orientation = (edge0 % edge1).normalize();
		}
		
void Triangle::setPhongVectors(const Vector nv0, const Vector nv1, const Vector nv2) {
	this->phongShading = true;
	this->nv0 = nv0;
	this->nv1 = nv1;
	this->nv2 = nv2;
}

void Triangle::setTextureVectors(const Vector vt0, const Vector vt1, const Vector vt2) {
	this->textureMap = true;
	this->phongShading = true;
	this->vt0 = vt0;
	this->vt1 = vt1;
	this->vt2 = vt2;
}
		
inline HitData *Triangle::hit(const Vector *ray, const Vector *pixelPosition) const {	
	HitData *hitData = Plane::hit(ray, pixelPosition);
	if (!hitData) return NULL;
	Vector hitPoint = hitData->hitPoint;
	double g = (edge0 % edge1 * (edge0 % (hitPoint - p0))) / pow((edge0 % edge1).magnitude(), 2);
	double a = (edge0 % edge1 * (edge1 % (hitPoint - p1))) / pow((edge0 % edge1).magnitude(), 2);
	double b = (edge0 % edge1 * (edge2 % (hitPoint - p2))) / pow((edge0 % edge1).magnitude(), 2);
	if (a > 1 || a < 0) {delete hitData; return NULL;}
	if (b > 1 || b < 0) {delete hitData; return NULL;}
	if (g > 1 || g < 0) {delete hitData; return NULL;}
	if (phongShading) hitData->surfaceNormal = nv0 + ((nv1 - nv0) * b) + ((nv2 - nv0) * g);
	if (textureMap) hitData->textureCoordinate = vt0 + ((vt1 - vt0) * b) + ((vt2 - vt0) * g);
	return hitData;
}
