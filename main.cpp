#include "RayTracer.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "ParallelLight.h"

int main() {
    RayTracer rayTracer;
    rayTracer.cameraViewPoint(Vector(0, -40, 25));
    rayTracer.cameraViewDirection(Vector(0, 1, -0.5));
    rayTracer.screenPixelWidth(600);
    rayTracer.cameraFocalLength(0.5);
    rayTracer.cameraOrientation(Vector(0,0,1));
    rayTracer.load("teapot-lite.obj");
    rayTracer.ambientLight(Color(0,0,0));
    //rayTracer.addLight(new SpotLight("SpotLight1", Color(1, 1, 1), Vector(0, 0, 100), Vector(0, 0, -1), 1, 20, 5));
    //rayTracer.addLight(new PointLight("PointLight1", Vector(0,0, 40), Color(1, 1, 1), 0.5));
    rayTracer.addLight(new ParallelLight("PointLight1", Color(1, 1, 1), Vector(0,0,0), Vector(0,1,0), 0.5));
    rayTracer.addLight(new ParallelLight("PointLight1", Color(1, 1, 1), Vector(0,0,0), Vector(0,0,-1), 0.5));
    //rayTracer.addLight(new ParallelLight("PointLight1", Color(1, 1, 1), Vector(0,0,0), Vector(1,0,0), 1));
    rayTracer.render();
    rayTracer.save("images/out.png");
    return 0;
}
