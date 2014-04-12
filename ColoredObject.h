#ifndef COLORED_OBJECT_H
#define COLORED_OBJECT_H

#include "Object.h"
#include "Color.h"

class ColoredObject : public Object {
   public:
      Color color;
      ColoredObject();
      ColoredObject(const Color color);
      ColoredObject(String name, const Color color);
      virtual ~ColoredObject();
      void setColor(const Color color);
};

#endif
