#include "Material.h"

Material::Material() :
		ColoredObject(Color(WHITE)),
		specularCoefficient(Color(BLACK)), 
		specularExponent(0), 
		diffusionCoefficient(Color(WHITE)),
		shadingModel(2),
		ambientTexture(NULL),
		diffuseTexture(NULL),
		specularTexture(NULL),
		textureAlpha(1) {}

Material::Material(String name) :
		ColoredObject(name, Color(WHITE)),
		specularCoefficient(Color(BLACK)), 
		specularExponent(0), 
		diffusionCoefficient(Color(WHITE)),
		shadingModel(2),
		ambientTexture(NULL),
		diffuseTexture(NULL),
		specularTexture(NULL),
		textureAlpha(1) {}
      
Material::Material(const enum Materials material) : 
		ColoredObject(), 		
		shadingModel(2),
		ambientTexture(NULL),
		diffuseTexture(NULL),
		specularTexture(NULL),
		textureAlpha(1) {
   switch (material) {
      case CHROME:
      	this->color = Color(WHITE);
      	specularCoefficient = Color(WHITE); 
			specularExponent = 1000; 
   		diffusionCoefficient = Color(BLACK);
       	break;
      case RED_GLASS:
      	this->color = Color(RED);
         specularCoefficient = Color(WHITE); 
   	 	specularExponent = 80; 
         diffusionCoefficient = Color(0.1, 0.1, 0.1);
         break;
       case GREEN_GLASS:
      	this->color = Color(GREEN);
         specularCoefficient = Color(WHITE); 
   	 	specularExponent = 80; 
         diffusionCoefficient = Color(0.1, 0.1, 0.1);
         break;
       case BLUE_GLASS:
      	this->color = Color(0, 0, 0);
         specularCoefficient = Color(0, 0, 0.5); 
   	 	specularExponent = 80; 
         diffusionCoefficient = Color(0, 0, 0.2);
         break;
       case PURPLE_GLASS:
      	this->color = Color(PURPLE);
         specularCoefficient = Color(WHITE); 
   	 	specularExponent = 80; 
         diffusionCoefficient = Color(0.1, 0.1, 0.1);
         break;
      case ORANGE_GLASS:
      	this->color = Color(ORANGE);
         specularCoefficient = Color(WHITE); 
         specularExponent = 80; 
         diffusionCoefficient = Color(0.1, 0.1, 0.1);
         break;
      case ORANGE_CLAY:
      	this->color = Color(ORANGE);
         specularCoefficient = Color(BLACK); 
         specularExponent = 0; 
         diffusionCoefficient = Color(WHITE);
         break;
      case RED_CLAY:
      	this->color = Color(RED);
         specularCoefficient = Color(BLACK); 
         specularExponent = 0; 
         diffusionCoefficient = Color(WHITE);
         break;
      case BLUE_CLAY:
      	this->color = Color(BLUE);
         specularCoefficient = Color(BLACK); 
         specularExponent = 0; 
         diffusionCoefficient = Color(WHITE);
         break;
      case GREEN_CLAY:
      	this->color = Color(RED);
         specularCoefficient = Color(BLACK); 
         specularExponent = 0; 
         diffusionCoefficient = Color(WHITE);
         break;
      case PURPLE_CLAY:
      	this->color = Color(RED);
         specularCoefficient = Color(BLACK); 
         specularExponent = 0; 
         diffusionCoefficient = Color(WHITE);
         break;
      case IVORY:
      	this->color = Color(WHITE);
         specularCoefficient = Color(0.8, 0.8, 0.8); 
         specularExponent = 20; 
         diffusionCoefficient = Color(0.7, 0.7, 0.7);
   }
}

