#include "RayTracer.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "ParallelLight.h"

int main() {
    RayTracer rayTracer;
    rayTracer.cameraViewPoint(Vector(0, -40, 35));
    rayTracer.cameraViewDirection(Vector(0, 1, -0.7));
    rayTracer.screenPixelWidth(600);
    rayTracer.cameraFocalLength(0.5);
    rayTracer.cameraOrientation(Vector(0,0,1));
    rayTracer.loadShape("teapot-lite.obj");
    rayTracer.ambientLight(Color(0,0,0));
    rayTracer.enableReflections();
    //rayTracer.addLight(new SpotLight("SpotLight1", Color(1, 1, 1), Vector(0, 0, 100), Vector(0, 0, -1), 1, 20, 5));
    rayTracer.addLight(new PointLight("PointLight1", Vector(0,40, 40), Color(1, 1, 1), 1));
    rayTracer.addLight(new PointLight("PointLight1", Vector(40,0,0), Color(1, 1, 1), 0.8));
    //rayTracer.addLight(new ParallelLight("PointLight1", Color(1, 1, 1), Vector(0,0,0), Vector(0,1,0), 0.5));
    //rayTracer.addLight(new ParallelLight("PointLight1", Color(1, 1, 1), Vector(0,0,0), Vector(0,0,-1), 0.5));
    //rayTracer.addLight(new ParallelLight("PointLight1", Color(1, 1, 1), Vector(0,0,0), Vector(1,1,0), 0.4));
    rayTracer.render();
    rayTracer.saveImage("images/out.png");
    return 0;
}
