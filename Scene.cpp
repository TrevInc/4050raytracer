#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {
	Node *node = shapes.head;
	while (node) {
		delete (Shape *)node->data;
		node = node->next;
	}
   node = lights.head;
	while (node) {
		delete (Light *)node->data;
		node = node->next;
	} 
}

void Scene::addShape(const Shape *shape) {shapes.add(shape);}

void Scene::addLight(const Light *light) {lights.add(light);}

void Scene::setAmbientLight(const Color color) {ambientLight = color;}
