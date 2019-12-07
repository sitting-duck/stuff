#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "Node.h"

using namespace std;

class BinaryTree{

public:
	Node root;

public:
	BinaryTree();
	~BinaryTree();

	void printLevelOrderTree();
};

#endif