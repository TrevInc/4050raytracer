#ifndef AABB_H
#define AABB_H

#include "Vector.h"

class BoundingBox { 
	private:
		Vector x0, x1, y0, y1, z0, z1;
		Vector locations[6];
		Vector normals[6];
		Vector points[6];
		bool inside;
		bool misses[6];
		double hit, t;
		int hitcount;
	public: 
		BoundingBox(const double x0, const double x1, const double y0, const double y1, const double z0, const double z1);
		bool intersect(const Vector *ray, const Vector *pixelPosition);
};

#endif


