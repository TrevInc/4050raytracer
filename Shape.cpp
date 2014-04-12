#include "Shape.h"

Shape::Shape(String name, const Material material) : 
	Object(name), 
	material(material) {}

Shape::~Shape() {}
