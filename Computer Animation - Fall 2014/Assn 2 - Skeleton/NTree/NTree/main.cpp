#include "tree.hh"
#include "tree_util.hh"

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <list>
#include <utility>
#include <stdexcept>

void print_tree(const tree<std::string>& _tree, tree<std::string>::pre_order_iterator _it, tree<std::string>::pre_order_iterator _end);

void main(){

	/*tree<std::string> tr;
	tree<std::string>::iterator one;
	tree<std::string>::sibling_iterator top;
	tree<std::string>::iterator end;
	
	tr.insert(top, "herp");
	//tr.insert(end, "derp");

	top = tr.begin();
	one = tr.append_child(one, "derp");
	std::cout << "begin: " << *top << std::endl;
	end = tr.end();
	std::cout << "end: " << *end << std::endl;
	int treeDepth = tr.depth(top);
	std::cout << "treeDepth " << treeDepth << std::endl;

	//tr.set_head("herp");
	

	//I have no idea what the purpose of these lines is
	tr.insert(tr.begin().begin(), "0");
	tr.insert(tr.begin().begin(), "1");
	
	//print_tree(tr, tr.begin(), tr.end());
	print_tree(tr, top, end);*/

	tree<std::string> tr;
	tree<std::string>::iterator top, one, two, loc, banana;

	top = tr.begin();
	one = tr.insert(top, "one");
	two = tr.append_child(one, "two");
	tr.append_child(two, "apple");
	banana = tr.append_child(two, "banana");
	tr.append_child(banana, "cherry");
	tr.append_child(two, "peach");
	tr.append_child(one, "three");

	loc = std::find(tr.begin(), tr.end(), "two");
	if (loc != tr.end()){
		tree<std::string>::sibling_iterator sib = tr.begin(loc);
		while (sib != tr.end(loc)){
			std::cout << (*sib) << std::endl;
			++sib;
		}
		std::cout << std::endl;
		tree<std::string>::iterator sib2 = tr.begin(loc);
		tree<std::string>::iterator end2 = tr.end(loc);
		while (sib2 != end2){
			for (int i = 0; i < tr.depth(sib2) - 2; ++i){
				std::cout << " ";
			}
			std::cout << (*sib2) << std::endl;
			++sib2;
		}
	}
}

/**
* param: _tree: an instance of tree
* param: _it : an instance of the preorder iterator for that tree.
* param: _end : an instance of an iterator pointing to the end of the tree
* An example call to this function would look like: 
*		print_tree(tr, tr.begin(), tr.end());
*/
void print_tree(const tree<std::string>& _tree, tree<std::string>::pre_order_iterator _it, tree<std::string>::pre_order_iterator _end){
	
	//if iterator points to a node that DNE or a dummy node, we exit
	if (!_tree.is_valid(_it))return;

	//depth refers to the distance from the root. The root has depth 0. A node on the 3rd level would have a depth of 2.
	int rootdepth = _tree.depth(_it);

	std::cout << "-----" << std::endl;
	
	while (_it != _end){
		for (int i = 0; i < _tree.depth(_it) - rootdepth; ++i){
			std::cout << " ";
			std::cout << (*_it) << std::endl << std::flush;
			++_it;
		}
	}
	std::cout << "-----" << std::endl;
}
