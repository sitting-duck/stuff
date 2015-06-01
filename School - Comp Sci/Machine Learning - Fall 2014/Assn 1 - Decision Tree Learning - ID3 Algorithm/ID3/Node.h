#ifndef NODE_H
#define NODE_H

#include "Attribute.h"

class Node{

public:
	
	Node();
	Node(string _name);
	~Node();

	Attribute attribute;

	Node* parent;
	Node* left;
	Node* right;
};

#endif