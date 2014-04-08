#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Plane.h"

class Triangle : public Plane {
	private:
		Vector p0, p1, p2, nv0, nv1, nv2, vt0, vt1, vt2, edge0, edge1, edge2;
		bool phongShading, textureMap;
		double area;
   public:
      Triangle(
      	String name, 
      	const enum Materials material, 
      	const Vector p0, 
      	const Vector p1, 
      	const Vector p2);
      Triangle(
      	String name,  
      	const Material material, 
      	const Vector p0, 
      	const Vector p1, 
      	const Vector p2);
      void setPhongVectors(const Vector nv0, const Vector nv1, const Vector nv2);
      void setTextureVectors(const Vector vt0, const Vector vt1, const Vector vt2);
      virtual HitData *hit(const Vector *ray, const Vector *pixelPosition) const;
};

#endif
