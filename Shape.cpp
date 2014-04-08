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
   Vector surfaceNormal = hitData->surfaceNormal;
   double lightIntensity = light->getIntensity(&hitData->hitPoint);
   if (material.shadingModel == 0) {
   	hitColor = material.diffusionCoefficient;
   } else if (material.shadingModel == 1) {
   	hitColor = (lightColor * lightIntensity * material.diffusionCoefficient) 
   		+ (material.diffusionCoefficient * (-lightRay * surfaceNormal));
   	if (material.diffuseTexture) {
   		hitColor += Color(material.diffuseTexture->getPixelAt(
   			(hitData->textureCoordinate.x * material.diffuseTexture->getRowSize()), 
   			(hitData->textureCoordinate.y * material.diffuseTexture->getColumnSize()))) 
   			* material.textureAlpha;
   	}
   } else if (material.shadingModel == 2) {
   	Color light = lightColor * lightIntensity * material.color;
   	if (material.ambientTexture) {
   		light += Color(material.ambientTexture->getPixelAt(
   			(hitData->textureCoordinate.x * material.diffuseTexture->getRowSize()), 
   			(hitData->textureCoordinate.y * material.diffuseTexture->getColumnSize()))) * material.textureAlpha;
   	}
   	hitColor = light + (material.diffusionCoefficient * (-lightRay * surfaceNormal));
   	if (material.diffuseTexture) {
   		hitColor += Color(material.diffuseTexture->getPixelAt(
   			(hitData->textureCoordinate.x * material.diffuseTexture->getRowSize()), 
   			(hitData->textureCoordinate.y * material.diffuseTexture->getColumnSize()))) * material.textureAlpha;
   	}
   	hitColor += light * pow((lightRay - (surfaceNormal * 2 * (surfaceNormal * lightRay))).normalize()
   		* hitData->viewRay, material.specularExponent) * material.specularCoefficient;
   	if (material.specularTexture) {
   		hitColor += Color(material.specularTexture->getPixelAt(
   			(hitData->textureCoordinate.x * material.diffuseTexture->getRowSize()), 
   			(hitData->textureCoordinate.y * material.diffuseTexture->getColumnSize()))) * material.textureAlpha;
   	}
   }
   return hitColor;
}
