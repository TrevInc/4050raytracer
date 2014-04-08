#ifndef HIT_DATA_H
#define HIT_DATA_H

#include "Vector.h"
#include "Object.h"

struct HitData {
     Vector hitPoint;
     Vector pixelPosition;
     Vector viewRay;
     Vector surfaceNormal;
     Vector reflectionRay;
     Vector textureCoordinate;
     const Object *hitObject;
     double distance;
};

#endif
