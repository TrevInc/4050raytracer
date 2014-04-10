#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "String.h"
#include "Parser.h"
#include "Camera.h"
#include "Scene.h"

class RayTracer {
    private:
        Scene scene;
        Parser parser;
        Pixmap *pixmap;
        Camera camera;
    public:
        RayTracer();
        ~RayTracer();
        void addShape(const Shape *shape);
        void addLight(const Light *light);
        void loadObject(String *path);
        void save(const char *path);
        void render();
};

#endif
