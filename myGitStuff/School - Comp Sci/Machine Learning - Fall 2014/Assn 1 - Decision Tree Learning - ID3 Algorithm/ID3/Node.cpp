#include "Node.h"

Node::Node() :left(NULL), right(NULL), parent(NULL){
	attribute = Attribute();
}

Node::Node(string _name) : left(NULL), right(NULL), parent(NULL)
{
	attribute = Attribute(_name);
}

Node::~Node(){}