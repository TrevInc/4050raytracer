#include "List.h"

List::List() : size(0), head(NULL), tail(NULL) {}

List::~List() {
    Node *node = head;
    Node *next;
    while (node) {
        next = node;
        node = node->next;
        delete next;
    }
}

const void *List::getElementAtIndex(const int index) const {
 	Node *node = head;
	for (int ndx = 0; ndx < index; ndx++) node = node->next;
	return node->data;
}

const unsigned int List::getSize() const {return size;}

void List::add(const void *object) {
	Node *node = new Node(object);
   if (!head) head = node; 
   else tail->next = node;
   tail = node;
   ++size;
}
