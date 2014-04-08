#include "Object.h"

Object::Object() : name() {}

Object::Object(String name) : name(name) {}
      
const String Object::getName() const {return name;}

void Object::setName(const String name) {this->name = name;}
