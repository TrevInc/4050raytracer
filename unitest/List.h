#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include "Object.h"
#include <cstddef>

class List {
	private:
      unsigned int size;
	public:
      Node *head;
      Node *tail; 
      List();
      ~List();
      const void *getElementAtIndex(const int index) const;
      const unsigned int getSize() const;
      void add(const void *object);
};

#endif
