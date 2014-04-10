#ifndef NODE_H
#define NODE_H

#include "Object.h"
#include <cstddef>

class Node {
   public:
      const void *data;
      Node *next;
      Node(const void *data);
};

#endif
