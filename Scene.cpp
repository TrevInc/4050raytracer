#include "Scene.h"

Scene::Scene() : 
	shapes(new List()), 
	lights(new List()), 
	cameras(new List()), 
	images(new List()), 
	ambientLight(Color(BLACK)) {}

Scene::~Scene() {
	Node *node = shapes->head;
	while (node) {
		delete (Shape *)node->data;
		node = node->next;
	}
   delete shapes;
   node = lights->head;
	while (node) {
		delete (Light *)node->data;
		node = node->next;
	}
   delete lights;  
   node = cameras->head;
	while (node) {
		delete (Camera *)node->data;
		node = node->next;
	}
   delete cameras;
   node = images->head;
	while (node) {
		delete (Image *)node->data;
		node = node->next;
	}
   delete images;
}

List *Scene::getShapeList() const {return shapes;}

List *Scene::getLightList() const {return lights;}

void Scene::addShape(const Shape *shape) {shapes->add(shape);}

void Scene::addLight(const Light *light) {lights->add(light);}

void Scene::addCamera(const Camera *camera) {cameras->add(camera);}

void Scene::setAmbientLight(const Color ambientLight) {this->ambientLight = ambientLight;}

const Color Scene::getAmbientLight() const {return ambientLight;}

void Scene::renderImages() {
    Node *node = cameras->head;
    Camera *camera;
    Pixmap *pixmap;
    while (node) {
        camera = (Camera *)node->data;
        camera->setShapes(shapes);
        camera->setLights(lights);
        camera->setAmbientLight(ambientLight);
        pixmap = camera->captureImage();
        images->add(pixmap);
        node = node->next;
    }
}

List *Scene::getImages() const {return images;}
