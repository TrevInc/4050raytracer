#ifndef LIST_H
#define LIST_H

#include <cstddef>

struct Node {
	const void *data;
   Node *next;
};

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
