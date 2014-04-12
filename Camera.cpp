#include "Camera.h"

Camera::Camera() : 
   screenWidth(0.5), 
   aspectRatio(1.25), 
   focalLength(0.5), 
   screenPixelWidth(250), 
   antialiasingLevel(1),
   recursionLevel(5),
   viewPoint(Vector(0, 0, 0.5)), 
   direction(Vector(0, 0, -1)), 
   up(Vector(0, 1, 0)), 
   projectionView(true), 
   antialiasing(false),
   scene(NULL) {}
      
inline HitData *Camera::trace(const Vector *ray, const Vector *pixelPosition) {
   List hitShapes;
   HitData *hitData, *closestHit(NULL);
   Node *node(scene->shapes.head);     
   double previousDistance(MAX_DOUBLE);
   while (node) {
      hitData = ((Shape *)node->data)->hit(ray, pixelPosition);
      if (hitData) hitShapes.add(new HitData(*hitData));
      if (hitData) delete hitData;
      node = node->next;
   }
   node = hitShapes.head;
   while (node) {
      hitData = (HitData *)node->data;
      if (hitData->distance < previousDistance) {
         previousDistance = hitData->distance;
         if (closestHit) delete closestHit; 
         closestHit = new HitData(*hitData);
      } 
      if (hitData) delete hitData;
      node = node->next;
   }
   return closestHit;
}

inline Color Camera::shade(const HitData *hitData) {
	Color color; 
   static int depth(0);
   if (++depth < recursionLevel && hitData) {
      Shape *shape((Shape *)hitData->hitObject);
   	Light *light;
   	Vector lightRay;
   	HitData *hit, *shadow;
   	Node *node(scene->lights.head);
      while (node) {
         light = (Light *)node->data;
         lightRay = -light->getLightRay(&hitData->hitPoint);
         shadow = trace(&lightRay, &hitData->hitPoint);
         if (!shadow) { 
   			Color lightColor = light->color * light->getIntensity(&hitData->hitPoint);
				lightRay = light->getLightRay(&hitData->hitPoint);
   			Vector surfaceNormal = hitData->surfaceNormal;
   			Material material = shape->material;
   			switch (material.shadingModel) {
   				case 0:
   					color += material.diffusionCoefficient;
   					break;
   				case 1:
   					if (material.ambientTexture) {
   						Color textureColor = material.ambientTexture->getPixelAt(
   							(hitData->textureCoordinate.x * material.ambientTexture->getRowSize()), 
   							(hitData->textureCoordinate.y * material.ambientTexture->getColumnSize()));
   						color += lightColor * textureColor;
   					} else color += lightColor * material.color;
   					if (material.diffuseTexture) {
   						Color textureColor = material.diffuseTexture->getPixelAt(
   							(hitData->textureCoordinate.x * material.diffuseTexture->getRowSize()), 
   							(hitData->textureCoordinate.y * material.diffuseTexture->getColumnSize()));
   						color += lightColor * textureColor * (-lightRay * surfaceNormal);
   					} else color += lightColor * material.diffusionCoefficient * (-lightRay * surfaceNormal);
   					break;
   				case 2:
   					if (material.ambientTexture) {
   						Color textureColor = material.ambientTexture->getPixelAt(
   							(hitData->textureCoordinate.x * material.ambientTexture->getRowSize()), 
   							(hitData->textureCoordinate.y * material.ambientTexture->getColumnSize()));
   						color = lightColor * textureColor;
   					} else color = lightColor * material.color;
   					if (material.diffuseTexture) {
   						Color textureColor = material.diffuseTexture->getPixelAt(
   							(hitData->textureCoordinate.x * material.diffuseTexture->getRowSize()), 
   							(hitData->textureCoordinate.y * material.diffuseTexture->getColumnSize()));
   						color += lightColor * textureColor * (-lightRay * surfaceNormal);
   					} else color += lightColor * material.diffusionCoefficient * (-lightRay * surfaceNormal);
   					color += lightColor * pow((lightRay - (surfaceNormal * 2 * (surfaceNormal * lightRay))).normalize()
   						* hitData->viewRay, material.specularExponent) * material.specularCoefficient;
   					hit = trace(&hitData->reflectionRay, &hitData->hitPoint);
   					color += shade(hit) * shape->material.specularCoefficient;
   					delete hit;
   			}
         } else {
         	if (shape->material.ambientTexture) {
         		color += scene->ambientLight * shape->material.ambientTexture->getPixelAt(
         			hitData->textureCoordinate.x * shape->material.ambientTexture->getRowSize(),
         			hitData->textureCoordinate.y * shape->material.ambientTexture->getRowSize());
         	} else color += shape->material.color;
         	delete shadow;
         }
         node = node->next;
      }
   	color += scene->ambientLight;
   }
   depth = 0;
   return color;
}
      
Pixmap *Camera::captureImage() {
	double screenHeight(screenWidth / aspectRatio);
   int screenPixelHeight(screenPixelWidth / aspectRatio);
   Pixmap *pixmap(new Pixmap(screenPixelWidth, screenPixelHeight));
   double pixelHeight(screenHeight / screenPixelHeight);
   double pixelWidth(screenWidth / screenPixelWidth);
   double centerWidth(-screenWidth / 2);
   double centerHeight(-screenHeight / 2);
   Vector screenCenter(viewPoint + (direction * focalLength));
   Vector u_x((direction % up).normalize());
   Vector u_y(-direction % u_x);
   Vector pixelPosition, ray;
   HitData *hitData;
   Color color;
   double r, g, b;
   for (int i(0); i < screenPixelHeight; ++i) {
      for (int j(0); j < screenPixelWidth; ++j) {
         r = 0, g = 0, b = 0;
         for (int k(0); k < antialiasingLevel; ++k) {
         	pixelPosition = screenCenter 
         		+ (u_x * (centerWidth + pixelWidth * (j + (antialiasing?randf(0, 1):0.5)))) 
         		+ (u_y * (centerHeight + pixelHeight * (i + (antialiasing?randf(0, 1):0.5))));
         	if (projectionView) ray = (pixelPosition - viewPoint).normalize();
         	else ray = direction;
				hitData = trace(&ray, &pixelPosition);
        		color = shade(hitData);
        		if (hitData) delete hitData;
        		r += color.red;
        		g += color.green;
        		b += color.blue;
         }
         color = Color(r / antialiasingLevel, g / antialiasingLevel, b / antialiasingLevel);
         pixmap->setPixelAt(j, i, color.toPixel());	
      }
   }
   return pixmap;
}

void Camera::addScene(const Scene *scene) {
	this->scene = scene;
}

void Camera::setScreenWidth(const double width) {
	screenWidth = width;
}

void Camera::setScreenPixelWidth(const int pixels) {
	screenPixelWidth = pixels;
}

void Camera::setAspectRatio(const double ratio) {
	aspectRatio = ratio;
}

void Camera::setFocalLength(const double focalLength) {
	this->focalLength = focalLength;
}

void Camera::setViewPoint(const Vector viewPoint) {
	this->viewPoint = viewPoint;
}

void Camera::setViewDirection(const Vector direction) {
	this->direction = direction.normalize();
}

void Camera::setUpDirection(const Vector up) {
	this->up = up.normalize();
}

void Camera::setProjectionView() {
	projectionView = true;
}

void Camera::setOrthographicView() {
	projectionView = false;
}

void Camera::enableAntialiasing() {
	antialiasing = true;
}

void Camera::disableAntialiasing() {
	antialiasing = false;
}

void Camera::setRecursionLevel(const int level) {
	recursionLevel = level;
}

void Camera::setAntialiasingLevel(const int level) {
	antialiasingLevel < 1 ? antialiasingLevel = 1 : antialiasingLevel = level;
}

inline double Camera::randf(double min, double max) {
    double f = static_cast<double>(rand()) / RAND_MAX;
    return min + f * (max - min);
}
