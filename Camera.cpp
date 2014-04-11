#include "Camera.h"

Camera::Camera() : 
   screenWidth(0.5), 
   aspectRatio(1.25), 
   focalLength(0.5), 
   screenPixelWidth(250), 
   viewPoint(Vector(0, 0, 0.5)), 
   direction(Vector(0, 0, -1)), 
   up(Vector(0, 1, 0)), 
   projectionView(true), 
   antialiasing(false),
   antialiasingLevel(1),
   recursionLevel(5),
   shapes(NULL),
   lights(NULL),
   ambientLight(Color(BLACK)) {}
      
inline HitData *Camera::trace(const Vector *ray, const Vector *pixelPosition) {
   List hitShapes;
   HitData *hitData, *closestHit = NULL;
   Node *node;     
   double previousDistance = MAX_DOUBLE;
   node = shapes->head;
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
   Shape *shape;
   Light *light;
   Color color, reflected, black;
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
         if (!shadow) {
         	if (shape->material.ambientTexture) {
         		color += shape->shade(hitData, light) + ambientLight * shape->material.ambientTexture->getPixelAt(
         			hitData->textureCoordinate.x * shape->material.ambientTexture->getRowSize(),
         			hitData->textureCoordinate.y * shape->material.ambientTexture->getRowSize());
         	} else color += shape->shade(hitData, light);
         } else {
         	if (shape->material.ambientTexture) {
         		color += ambientLight * shape->material.ambientTexture->getPixelAt(
         			hitData->textureCoordinate.x * shape->material.ambientTexture->getRowSize(),
         			hitData->textureCoordinate.y * shape->material.ambientTexture->getRowSize());
         	} else color += shape->material.color;
         	delete shadow;
         }
         node = node->next;
      }
      if (shape->material.specularCoefficient != black) {
      	hit = trace(&hitData->reflectionRay, &hitData->hitPoint);
   		color += shade(hit) * shape->material.specularCoefficient;
   		delete hit;
   	}
   	color += ambientLight;
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
         for (int k = 0; k < antialiasingLevel; ++k) {
         	pixelPosition = screenCenter 
         		+ (u_x * (centerWidth + pixelWidth * (j + (antialiasing?randf(0, 1):0.5)))) 
         		+ (u_y * (centerHeight + pixelHeight * (i + (antialiasing?randf(0, 1):0.5))));
         	if (projectionView) ray = (pixelPosition - viewPoint).normalize();
         	else ray = direction;
				hitData = trace(&ray, &pixelPosition);
        		color = shade(hitData);
        		if (hitData) delete hitData;
        		r += color.getRed();
        		g += color.getGreen();
        		b += color.getBlue();
         }
         color = Color(r / antialiasingLevel, g / antialiasingLevel, b / antialiasingLevel);
         pixmap->setPixelAt(j, i, color.toPixel());	
      }
      std::cout << "%" <<  (int)(((double)i/(double)screenPixelWidth) * 100.0 + 20) << std::endl;
   }
   std::cout << "%100" << std::endl;
   return pixmap;
}

void Camera::setShapes(const List *shapes) {
	this->shapes = shapes;
}

void Camera::setLights(const List *lights) {
	this->lights = lights;
}

void Camera::setAmbientLight(const Color color) {
	ambientLight = color;
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

double Camera::randf(double min, double max) {
    double f = static_cast<double>(rand()) / RAND_MAX;
    return min + f * (max - min);
}
