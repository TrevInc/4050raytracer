#include "RayTracer.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "ParallelLight.h"

int main() {
    RayTracer rayTracer;
    rayTracer.cameraViewPoint(Vector(0, -40, 32));
    rayTracer.cameraViewDirection(Vector(0, 1, -0.7));
    rayTracer.screenPixelWidth(600);
    rayTracer.cameraFocalLength(0.5);
    rayTracer.cameraOrientation(Vector(0,0,1));
    rayTracer.loadShape("models/teapot.obj");
    rayTracer.ambientLight(Color(0.1,0.1,0.1));
    rayTracer.enableReflections();
    rayTracer.addLight(new ParallelLight("PointLight1", Color(1, 1, 1), Vector(0,0,0), Vector(1,-1,-1), 0.6));
    rayTracer.render();
    rayTracer.saveImage("images/out.png");
    return 0;
}
