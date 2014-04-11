#ifndef RAY_TRACER_H
#define RAY_TRACER_H

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
       	void load(const char *path);
       	void save(const char *path);
       	void render();
       	Pixmap *getPixmap() const;
       	void ambientLight(const double r, const double g, const double b);
       	void aspectRatio(const double ratio);
       	void screenWidth(const double width);
			void screenPixelWidth(const int pixels);
			void cameraAspectRatio(const double aspectRatio);
			void cameraFocalLength(const double focalLength);
			void cameraViewPoint(const double x, const double y, const double z);
			void cameraViewDirection(const double x, const double y, const double z);
			void cameraOrientation(const double x, const double y, const double z);
			void enableProjectionView();
			void enableOrthographicView();
			void enableAntialiasing();
			void disableAntialiasing();
			void recursionLevel(const int level);
			void antialiasingLevel(const int level);
};

#endif
