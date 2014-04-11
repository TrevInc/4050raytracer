#include "RayTracer.h"
#include "SpotLight.h"
#include "PointLight.h"

int main() {  
    RayTracer rayTracer;
    rayTracer.cameraViewPoint(4, 0, 4);
    rayTracer.cameraViewDirection(-1, 0, -1);
    rayTracer.screenPixelWidth(1024);
    rayTracer.cameraFocalLength(0.5);
    rayTracer.load("tetrahedron.obj");
    rayTracer.addLight(new SpotLight("SpotLight1", Color(WHITE), Vector(0, 0, 5), Vector(-0.5, 0, -1), 1, 20, 10));
    rayTracer.addLight(new PointLight("PointLight1", Vector(2, 0, 1), Color(WHITE), 0.5));
    rayTracer.render();
    rayTracer.save("images/out.png");
    return 0;
}
