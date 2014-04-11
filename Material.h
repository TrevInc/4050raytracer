#ifndef MATERIAL_H
#define MATERIAL_H

#include "EnumMaterials.h"
#include "ColoredObject.h"
#include "Pixmap.h"

class Material : public ColoredObject {
   public:
      Color specularCoefficient, diffusionCoefficient;;
      double specularExponent, textureAlpha;
      short int shadingModel;
      Pixmap *ambientTexture, *diffuseTexture, *specularTexture;
      Material();
      Material(String name);
      Material(const enum Materials material);
};

#endif
