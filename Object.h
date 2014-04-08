#ifndef OBJECT_H
#define OBJECT_H

#include "String.h"

class Object {
   protected:
      String name;
   public:
      Object();
      Object(String name);
      const String getName() const;
      void setName(const String name);
};

#endif
