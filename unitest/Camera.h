#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"
#include "Image.h"
#include "Pixmap.h"
#include "Color.h"
#include "HitData.h"
#include "Object.h"
#include "List.h"
#include "Shape.h"
#include <pthread.h>

#define MAX_DOUBLE 100000000000000000

class Camera : public Object {
   private:
      double screenWidth; 
      double aspectRatio;
      double focalLength;
      int screenPixelWidth;
      Vector viewPoint; 
      Vector direction;
      Vector up;
      bool projectionView;
      bool antialiasing;
      unsigned short int level;
      unsigned short int recursionLevel;
      const List *shapes;
      const List *lights;
      Color ambientLight;
      HitData *trace(const Vector *ray, const Vector *pixelPosition);
      Color shade(const HitData *hitData);
      double randf(double min, double max);
   public:
      Camera();
      Pixmap *captureImage();
      void setShapes(const List *shapes);
      void setLights(const List *lights);
      void setAmbientLight(const Color ambientLight);
      void setAmbientLight(const enum Colors ambientLight);
      void setScreenWidth(const double screenWidth);
      void setScreenPixelWidth(const int screenPixelWidth);
      void setAspectRatio(const double aspectRatio);
      void setFocalLength(const double focalLength);
      void setViewPoint(const Vector viewPoint);
      void setDirection(const Vector direction);
      void setUpDirection(const Vector up);
      void setProjectionView();
      void setOrthographicView();
      void enableAntialiasing();
      void disableAntialiasing();
      void setRecursionLevel(const unsigned short int recursionLevel);
      void setAntialiasingLevel(const unsigned short int level);
};

#endif
