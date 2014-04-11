#include "RayTracer.h"

RayTracer::RayTracer() : pixmap(NULL) {}

RayTracer::~RayTracer() {
	if (pixmap) delete pixmap;
}

void RayTracer::addShape(const Shape *shape) {
	scene.addShape(shape);
}

void RayTracer::addLight(const Light *light) {
	scene.addLight(light);
}

void RayTracer::save(const char *path) {
	Image image;
	image.writeImage(path, pixmap);
}

void RayTracer::load(const char *path) {
	Parser parser;
	parser.parse(path);
	List *faces = parser.getFaces();
	Node *node = faces->head;
	while (node) {
		scene.addShape((Shape *)node->data);
		node = node->next;
	}
}

void RayTracer::render() {
	camera.setShapes(scene.getShapeList());
   camera.setLights(scene.getLightList());
   pixmap = camera.captureImage();
}

Pixmap *RayTracer::getPixmap() const {return pixmap;}

void RayTracer::ambientLight(const double r, const double g, const double b) {
	camera.setAmbientLight(Color(r, g, b));
}

void RayTracer::aspectRatio(const double ratio) {
	camera.setAspectRatio(ratio);
}

void RayTracer::screenWidth(const double screenWidth) {
	camera.setScreenWidth(screenWidth);
}

void RayTracer::screenPixelWidth(const int screenPixelWidth) {
	camera.setScreenPixelWidth(screenPixelWidth);
}

void RayTracer::cameraFocalLength(const double focalLength) {
	camera.setFocalLength(focalLength);
}

void RayTracer::cameraViewPoint(const double x, const double y, const double z) {
	camera.setViewPoint(Vector(x, y, z));
}

void RayTracer::cameraViewDirection(const double x, const double y, const double z) {
	camera.setViewDirection(Vector(x, y, z));
}

void RayTracer::cameraOrientation(const double x, const double y, const double z) {
	camera.setUpDirection(Vector(x, y, z));
}

void RayTracer::enableProjectionView() {
	camera.setProjectionView();
}

void RayTracer::enableOrthographicView() {
	camera.setOrthographicView();
}

void RayTracer::enableAntialiasing() {
	camera.enableAntialiasing();
}

void RayTracer::disableAntialiasing() {
	camera.disableAntialiasing();
}

void RayTracer::recursionLevel(const int level) {
	camera.setRecursionLevel(level);
}

void RayTracer::antialiasingLevel(const int level) {
	camera.setAntialiasingLevel(level);
}
