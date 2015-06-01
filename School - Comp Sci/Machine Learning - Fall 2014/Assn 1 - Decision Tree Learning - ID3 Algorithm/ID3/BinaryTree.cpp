
#include <list>
#include <iostream>
#include "BinaryTree.h"

using namespace std;

BinaryTree::BinaryTree(){
	root = Node();
}

BinaryTree::~BinaryTree(){

}

void BinaryTree::printLevelOrderTree(){
	if (root.attribute.name == ""){ return; }
	list<Node> currentLevel, nextLevel;

	currentLevel.push_front(root);

	Node currNode;
	while(!currentLevel.empty()){
		//cout << "is current level empty? " << currentLevel.empty() << endl;
		//cout << "is next level empty? " << nextLevel.empty() << endl;
		currNode = currentLevel.front();
		currentLevel.pop_front();
		//cout << "just popped currentLevel, is currentLevel empty? " << currentLevel.empty() << endl;
		//if (currNode){
			cout << currNode.attribute.name << " ";
			nextLevel.push_front(*(currNode.right));
			nextLevel.push_front(*(currNode.left));
		//}
		if (currentLevel.empty()){
			cout << endl;
			swap(currentLevel, nextLevel);
		}
	}
}


