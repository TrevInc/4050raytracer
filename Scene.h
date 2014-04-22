#ifndef SCENE_H
#define SCENE_H

#include "List.h"
#include "Shape.h"
#include "Light.h"

class Scene {
	public:
      List shapes;
      List lights;
      Color ambientLight;
      Scene();
      ~Scene();
      void addShape(const Shape *shape);
      void addLight(const Light *light);
      void setAmbientLight(const Color color);
};

#endif
