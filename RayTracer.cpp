#include "RayTracer.h"

RayTracer::RayTracer() : 
	scene(Scene()),
	parser(Parser()),
	pixmap(NULL), 
	camera(parser.parseConfig("config/camera.txt")) {}

RayTracer::~RayTracer() {
	if (pixmap) delete pixmap;
}

void RayTracer::addShape(const Shape *shape) {scene.addShape(shape);}

void RayTracer::addLight(const Light *light) {scene.addLight(light);}

void RayTracer::save(const char *path) {
	Image image;
	image.writeImage(path, pixmap);
}

void RayTracer::render() {
	camera.setShapes(scene.getShapeList());
   camera.setLights(scene.getLightList());
   pixmap = camera.captureImage();
}
