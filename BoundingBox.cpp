#include "BoundingBox.h"

BoundingBox::BoundingBox(const double x0, const double x1, const double y0, const double y1, const double z0, const double z1) : 
	x0(Vector(x0, 0, 0)), 
	x1(Vector(x1, 0, 0)), 
	y0(Vector(0, y0, 0)), 
	y1(Vector(0, y1, 0)), 
	z0(Vector(0, 0, z0)), 
	z1(Vector(0, 0, z1)) {
		locations[0] = this->x0;
		locations[1] = this->x1;
		locations[2] = this->y0;
		locations[3] = this->y1;
		locations[4] = this->z0;
		locations[5] = this->z1;
		normals[0] = this->x0.normalize();
		normals[1] = this->x1.normalize();
		normals[2] = this->y0.normalize();
		normals[3] = this->y1.normalize();
		normals[4] = this->z0.normalize();
		normals[5] = this->z1.normalize();
	}

bool BoundingBox::intersect(const Vector *ray, const Vector *pixelPosition) { 

	for (int ndx = 0; ndx < 6; ++ndx) {
		misses[ndx] = false;
		hit = *ray * normals[ndx];
		if (not hit) misses[ndx] = true;
		else {
			t = ((normals[ndx] * locations[ndx]) - (normals[ndx] * *pixelPosition)) / hit;
			if (not t) misses[ndx] = true;
			points[ndx] = *pixelPosition + (*ray * t);
		}
	}

	hitcount = 0;

   // check x0
   if (not misses[0] && hitcount < 2) {
   	inside = true;
   	if (points[0].y < locations[2].y) inside = false;
   	if (points[0].y > locations[3].y) inside = false;
   	if (points[0].z < locations[4].z) inside = false;
   	if (points[0].z > locations[5].z) inside = false;
   	if (inside) ++hitcount;
   }

   // check x1
   if (not misses[1] && hitcount < 2) {
   	inside = true;
   	if (points[1].y < locations[2].y) inside = false;
   	if (points[1].y > locations[3].y) inside = false;
   	if (points[1].z < locations[4].z) inside = false;
   	if (points[1].z > locations[5].z) inside = false;
   	if (inside) ++hitcount;
   }

   // check y0
   if (not misses[2] && hitcount < 2) {
   	inside = true;
   	if (points[2].x < locations[0].x) inside = false;
  		if (points[2].x > locations[1].x) inside = false;
   	if (points[2].z < locations[4].z) inside = false;
   	if (points[2].z > locations[5].z) inside = false;
   	if (inside) ++hitcount;
   }

   // check y1
   if (not misses[3] && hitcount < 2) {
   	inside = true;
   	if (points[3].x < locations[0].x) inside = false;
  		if (points[3].x > locations[1].x) inside = false;
   	if (points[3].z < locations[4].z) inside = false;
   	if (points[3].z > locations[5].z) inside = false;
   	if (inside) ++hitcount;
   }

   // check z0
   if (not misses[4] && hitcount < 2) {
   	inside = true;
   	if (points[4].x < locations[0].x) inside = false;
   	if (points[4].x > locations[1].x) inside = false;
   	if (points[4].y < locations[2].y) inside = false;
   	if (points[4].y > locations[3].y) inside = false;
   	if (inside) ++hitcount;
   }

   // check z1
   if (not misses[5] && hitcount < 2) {
   	inside = true;
   	if (points[5].x < locations[0].x) inside = false;
   	if (points[5].x > locations[1].x) inside = false;
   	if (points[5].y < locations[2].y) inside = false;
   	if (points[5].y > locations[3].y) inside = false;
   	if (inside) ++hitcount;
   }
   
   return (hitcount >= 2);
}
