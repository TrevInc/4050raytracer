#include "Material.h"

Material::Material() :
		ColoredObject(Color(1, 1, 1)),
		specularCoefficient(Color(0, 0, 0)),
		diffusionCoefficient(Color(1, 1, 1)),
		specularExponent(0),
		textureAlpha(1),
		shadingModel(2),
		ambientTexture(NULL),
		diffuseTexture(NULL) {}

Material::Material(String name) :
		ColoredObject(name, Color(1, 1, 1)),
		specularCoefficient(Color(0, 0, 0)),
		diffusionCoefficient(Color(1, 1, 1)), 
		specularExponent(0),
		textureAlpha(1),
		shadingModel(2),
		ambientTexture(NULL),
		diffuseTexture(NULL) {}
