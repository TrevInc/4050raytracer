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
   Vector lightRay = light->getLightRay(&hitData->hitPoint);
   Vector surfaceNormal = hitData->surfaceNormal;
   Color lightColor = light->color * light->getIntensity(&hitData->hitPoint);
   if (material.shadingModel == 0) {
   	hitColor = material.diffusionCoefficient;
   } else if (material.shadingModel == 1) {
   	if (material.ambientTexture) {
   		Color textureColor = material.ambientTexture->getPixelAt(
   			(hitData->textureCoordinate.x * material.ambientTexture->getRowSize()), 
   			(hitData->textureCoordinate.y * material.ambientTexture->getColumnSize()));
   		hitColor = lightColor * textureColor;
   	} else hitColor = lightColor * material.color;
   	if (material.diffuseTexture) {
   		Color textureColor = material.diffuseTexture->getPixelAt(
   			(hitData->textureCoordinate.x * material.diffuseTexture->getRowSize()), 
   			(hitData->textureCoordinate.y * material.diffuseTexture->getColumnSize()));
   		hitColor += lightColor * textureColor * (-lightRay * surfaceNormal);
   	} else hitColor += lightColor * material.diffusionCoefficient * (-lightRay * surfaceNormal);
   } else if (material.shadingModel == 2) {
   	if (material.ambientTexture) {
   		Color textureColor = material.ambientTexture->getPixelAt(
   			(hitData->textureCoordinate.x * material.ambientTexture->getRowSize()), 
   			(hitData->textureCoordinate.y * material.ambientTexture->getColumnSize()));
   		hitColor = lightColor * textureColor;
   	} else hitColor = lightColor * material.color;
   	if (material.diffuseTexture) {
   		Color textureColor = material.diffuseTexture->getPixelAt(
   			(hitData->textureCoordinate.x * material.diffuseTexture->getRowSize()), 
   			(hitData->textureCoordinate.y * material.diffuseTexture->getColumnSize()));
   		hitColor += lightColor * textureColor * (-lightRay * surfaceNormal);
   	} else hitColor += lightColor * material.diffusionCoefficient * (-lightRay * surfaceNormal);
   	hitColor += lightColor * pow((lightRay - (surfaceNormal * 2 * (surfaceNormal * lightRay))).normalize()
   		* hitData->viewRay, material.specularExponent) * material.specularCoefficient;
   }
   return hitColor;
}
