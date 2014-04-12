#include "ColoredObject.h"

ColoredObject::ColoredObject() : Object(), color(Color()) {}

ColoredObject::ColoredObject(
	const Color color) : 
		Object(), 
		color(color) {}

ColoredObject::ColoredObject(
	String name, 
	const Color color) : 
		Object(name), 
		color(color) {}

ColoredObject::~ColoredObject() {}

void  ColoredObject::setColor(const Color color) {this->color = color;}
