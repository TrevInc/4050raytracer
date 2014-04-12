#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"
#include "Image.h"
#include "Pixmap.h"
#include "Color.h"
#include "HitData.h"
#include "List.h"
#include "Shape.h"
#include "Scene.h"

#define MAX_DOUBLE 100000000000000000

class Camera {
   private:
      double screenWidth, aspectRatio, focalLength;
      int screenPixelWidth, antialiasingLevel, recursionLevel;
      Vector viewPoint, direction, up;
      bool projectionView, antialiasing;
      HitData *trace(const Vector *ray, const Vector *pixelPosition);
      Color shade(const HitData *hitData);
      const Scene *scene;
      double randf(double min, double max);
   public:
      Camera();
      Pixmap *captureImage();
      void addScene(const Scene *scene);
      void setScreenWidth(const double width);
      void setScreenPixelWidth(const int pixels);
      void setAspectRatio(const double ratio);
      void setFocalLength(const double focalLength);
      void setViewPoint(const Vector viewPoint);
      void setViewDirection(const Vector direction);
      void setUpDirection(const Vector up);
      void setProjectionView();
      void setOrthographicView();
      void enableAntialiasing();
      void disableAntialiasing();
      void setRecursionLevel(const int level);
      void setAntialiasingLevel(const int level);
};

#endif
