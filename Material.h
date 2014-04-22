#ifndef MATERIAL_H
#define MATERIAL_H

#include "ColoredObject.h"
#include "Pixmap.h"

class Material : public ColoredObject {
   public:
      Color specularCoefficient, diffusionCoefficient;;
      double specularExponent, textureAlpha;
      short unsigned int shadingModel;
      Pixmap *ambientTexture, *diffuseTexture;
      Material();
      Material(String name);
};

#endif
