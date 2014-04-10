#include "Camera.h"

Camera::Camera() :
	Object(), 
   screenWidth(0.5), 
   aspectRatio(1.25), 
   focalLength(0.5), 
   screenPixelWidth(250), 
   viewPoint(Vector(0, 0, 0.5)), 
   direction(Vector(0, 0, -1)), 
   up(Vector(0, 1, 0)), 
   projectionView(true), 
   antialiasing(false),
   level(1),
   recursionLevel(5),
   shapes(NULL),
   lights(NULL),
   ambientLight(Color(BLACK)) {}
      
inline HitData *Camera::trace(const Vector *ray, const Vector *pixelPosition) {
   List hitShapes;
   HitData *hitData, *closestHit = NULL;
   Node *node;     
   Shape *shape;
   double previousDistance = MAX_DOUBLE;
   node = shapes->head;
   while (node) {
      shape = (Shape *)node->data;
      hitData = shape->hit(ray, pixelPosition);
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
   Shape *shape;
   Light *light;
   Color color, reflected;
   HitData *hit, *shadow;
   Node *node;
   Vector lightRay;
   static int depth = 0;
   if (++depth < recursionLevel && hitData) {
      shape = (Shape *)hitData->hitObject;
      node = lights->head;
      while (node) {
         light = (Light *)node->data;
         lightRay = -light->getLightRay(&hitData->hitPoint);
         shadow = trace(&lightRay, &hitData->hitPoint);
         if (!shadow) color = color + shape->shade(hitData, light);	
        	else delete shadow;
         node = node->next;
      }
      hit = trace(&hitData->reflectionRay, &hitData->hitPoint);
   	color += shade(hit) * shape->material.specularCoefficient + ambientLight;
   	delete hit;
   }
   depth = 0;
   return color;
}
      
Pixmap *Camera::captureImage() {
	double screenHeight = screenWidth / aspectRatio;
   int screenPixelHeight = screenPixelWidth / aspectRatio;
   Pixmap *pixmap = new Pixmap(screenPixelWidth, screenPixelHeight);
   double pixelHeight = screenHeight / screenPixelHeight;
   double pixelWidth = screenWidth / screenPixelWidth;
   double centerWidth = -screenWidth / 2;
   double centerHeight = -screenHeight / 2;
   Vector screenCenter = viewPoint + (direction * focalLength);
   Vector u_x = (direction % up).normalize();
   Vector u_y = -direction % u_x;
   Vector pixelPosition, ray;
   HitData *hitData;
   Color color;
   double r, g, b;
   for (int i = 0; i < screenPixelHeight; ++i) {
      for (int j = 0; j < screenPixelWidth; ++j) {
         r = 0, g = 0, b = 0;
         for (int k = 0; k < level; ++k) {
         	pixelPosition = screenCenter 
         		+ (u_x * (centerWidth + pixelWidth * (j + (antialiasing?randf(0, 1):0.5)))) 
         		+ (u_y * (centerHeight + pixelHeight * (i + (antialiasing?randf(0, 1):0.5))));
         	if (projectionView) ray = (pixelPosition - viewPoint).normalize();
         	else ray = direction;
         	hitData = trace(&ray, &pixelPosition);
        		color = shade(hitData);
        		r += color.getRed();
        		g += color.getGreen();
        		b += color.getBlue();
        		if (hitData) delete hitData;
         }
         color = Color(r / level, g / level, b / level);
         pixmap->setPixelAt(j, i, color.toPixel());	
      }
   }
   return pixmap;
}

void Camera::setShapes(const List *shapes) {this->shapes = shapes;}

void Camera::setLights(const List *lights) {this->lights = lights;}

void Camera::setAmbientLight(const Color ambientLight) {this->ambientLight = ambientLight;}

void Camera::setAmbientLight(const enum Colors ambientLight) {this->ambientLight = Color(ambientLight);}

void Camera::setScreenWidth(const double screenWidth) {this->screenWidth = screenWidth;}

void Camera::setScreenPixelWidth(const int screenPixelWidth) {this->screenPixelWidth = screenPixelWidth;}

void Camera::setAspectRatio(const double aspectRatio) {this->aspectRatio = aspectRatio;}

void Camera::setFocalLength(const double focalLength) {this->focalLength = focalLength;}

void Camera::setViewPoint(const Vector viewPoint) {this->viewPoint = viewPoint;}

void Camera::setDirection(const Vector direction) {this->direction = direction;}

void Camera::setUpDirection(const Vector up) {this->up = up;}

void Camera::setProjectionView() {projectionView = true;}

void Camera::setOrthographicView() {projectionView = false;}

void Camera::enableAntialiasing() {antialiasing = true;}

void Camera::disableAntialiasing() {antialiasing = false;}

void Camera::setRecursionLevel(const unsigned short int recursionLevel) {this->recursionLevel = recursionLevel;}

void Camera::setAntialiasingLevel(const unsigned short int level) {level < 1 ? this->level = 1 : this->level = level;}

double Camera::randf(double min, double max) {
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}
