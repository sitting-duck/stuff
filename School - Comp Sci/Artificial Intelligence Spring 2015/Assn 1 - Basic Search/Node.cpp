
#include "Node.h"

Node::Node()
{
	state = "";
	parent = NULL;
	cost = 0;
	action = -1;
}


Node::Node(std::string& _state, int _action, Node* _parent, unsigned int _cost)
{
	state = _state;
	parent = _parent;
	cost = 0;
	action = _action;
	cost = _cost;
}

Node& Node::operator=(const Node& otherNode)
{
	state = otherNode.state;
	parent = otherNode.parent;
	cost = 0;
	action = otherNode.action;
	cost = otherNode.cost;
	return *this;
}

Node::Node(const Node& _node)
{
	parent = _node.parent;
	state = _node.state;
	cost = _node.cost;
	action = _node.action;
}

Node::~Node()
{

}