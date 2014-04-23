#include "RayTracer.h"

RayTracer::RayTracer() : pixmap(NULL) {}

RayTracer::~RayTracer() {delete pixmap;}

void RayTracer::addLight(const Light *light) {scene.addLight(light);}

void RayTracer::saveImage(const char *path) {
	Image image;
	image.writeImage(path, pixmap);
}

void RayTracer::loadShape(const char *path) {
	Parser parser;
	parser.parse(path);
	const List *faces = parser.getFaces();
	Node *node = faces->head;
	while (node) {
		scene.addShape((Shape *)node->data);
		node = node->next;
	}
}

const Pixmap *RayTracer::getPixmap() const {return pixmap;}

const Scene *RayTracer::getScene() const {return &scene;}

void RayTracer::render() {
	camera.addScene(&scene);
   pixmap = camera.captureImage();
}

void RayTracer::aspectRatio(const double ratio) {camera.setAspectRatio(ratio);}

void RayTracer::screenWidth(const double screenWidth) {camera.setScreenWidth(screenWidth);}

void RayTracer::screenPixelWidth(const int screenPixelWidth) {camera.setScreenPixelWidth(screenPixelWidth);}

void RayTracer::cameraFocalLength(const double focalLength) {camera.setFocalLength(focalLength);}

void RayTracer::cameraViewPoint(const Vector viewPoint) {camera.setViewPoint(viewPoint);}

void RayTracer::cameraViewDirection(const Vector direction) {camera.setViewDirection(direction);}

void RayTracer::cameraOrientation(const Vector orientation) {camera.setUpDirection(orientation);}

void RayTracer::enableProjectionView() {camera.setProjectionView();}

void RayTracer::enableOrthographicView() {camera.setOrthographicView();}

void RayTracer::enableAntialiasing() {camera.enableAntialiasing();}

void RayTracer::disableAntialiasing() {camera.disableAntialiasing();}

void RayTracer::recursionLevel(const int level) {camera.setRecursionLevel(level);}

void RayTracer::antialiasingLevel(const int level) {camera.setAntialiasingLevel(level);}

void RayTracer::ambientLight(const Color color) {scene.setAmbientLight(color);}

void RayTracer::enableReflections() {camera.enableReflections();}

void RayTracer::disableReflections() {camera.disableReflections();}
