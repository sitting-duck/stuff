#ifndef NODE_H
#define NODE_H

#include <string>
class Problem;

class Node
{

	friend Problem;

private:
	Node* parent;
	std::string state;
	int action;
	unsigned int cost;

public:
	Node();
	Node(std::string& _state, int action, Node* _parent, unsigned int _cost = 0);
	Node& operator=(const Node& otherNode);
	Node(const Node& _node);
	~Node();
};

#endif