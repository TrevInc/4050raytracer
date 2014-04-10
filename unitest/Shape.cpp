#include "Shape.h"

Shape::Shape(const Material material) : 
	Object(), 
	material(material) {}

Shape::Shape(String name, const Material material) : 
	Object(name), 
	material(material) {}

Shape::Shape(String name, const enum Materials material) : 
	Object(name), 
	material(material) {}

Shape::~Shape() {}

inline Color Shape::shade(const HitData *hitData, const Light *light) const {
   Color hitColor;
   Color lightColor = light->color;
   Vector lightRay = light->getLightRay(&hitData->hitPoint);
   double lightIntensity = light->getIntensity(hitData->hitPoint);
   if (material.shadingModel == 0) {
   	hitColor = material.diffusionCoefficient;
   } else if (material.shadingModel == 1) {
   	hitColor = (lightColor * lightIntensity * material.color * (-lightRay * hitData->surfaceNormal)
   		* material.diffusionCoefficient) + (lightColor * lightIntensity * material.color);
   } else if (material.shadingModel == 2) {
   	hitColor = (lightColor * lightIntensity * material.color * (-lightRay * hitData->surfaceNormal)
   		* material.diffusionCoefficient) + (lightColor * lightIntensity * material.color 
   		* pow((lightRay - (hitData->surfaceNormal * 2 * (hitData->surfaceNormal * lightRay))).normalize()
   		* hitData->viewRay, material.specularExponent) * material.specularCoefficient);
   }
   return hitColor;
}
