#ifndef SCENE_H
#define SCENE_H

#include "Node.h"
#include "List.h"
#include "Shape.h"
#include "Light.h"
#include "Camera.h"

class Scene {
   private:
      List *shapes;
      List *lights;
      List *cameras;
      List *images;
      Color ambientLight;
   public:
      Scene();
      ~Scene();
      List *getShapeList() const;
      List *getLightList() const;
      void addShape(const Shape *shape);
      void addLight(const Light *light);
      void addCamera(const Camera *camera);
      void setAmbientLight(const Color ambientLight);
      const Color getAmbientLight() const;
      void renderImages();
      List *getImages() const;
};

#endif
