#ifndef SHAPE_H
#define SHAPE_H

#include "Vector.h"
#include "Object.h"
#include "HitData.h"
#include "Light.h"
#include "Material.h"

class Shape : public Object {
   public:
      Material material;
		Shape(String name, const Material material);
		virtual ~Shape();
      virtual HitData *hit(const Vector *ray, const Vector *pixelPosition) const = 0;
};

#endif
