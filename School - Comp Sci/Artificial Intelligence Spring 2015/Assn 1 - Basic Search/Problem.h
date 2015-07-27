#ifndef PROBLEM_H
#define PROBLEM_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <set>
#include "Node.h"

class Problem
{
public:

	//if the user specifies via command line that we want to take cost into account, then cost will be the number of positions the tile moves
	static bool hasCost;

	enum SearchType { NOT_A_SEARCH_TYPE = -1, BFS, DFS, UCS, GS, ASTAR };

	SearchType currentSearchType;

	//the goal state (ie, all black tiles are to the left of the space and all white tiles are to the right of the space)
	static std::string goalState;

	Node root;	

	//this will hold all the nodes, the rest of the program will just pass around pointers to these nodes
	unsigned int chunkSize;
	
	/*the purpose of keeping this node storage array is so that we can pass around references to the nodes instead of actual copies of the nodes.*/
	Node* nodeStorage;
	unsigned int nodesInStorage;

	//this queue will hold the set of unvisited states. Each state must be checked that it has not yet been visited before it can be entered into this queue. This queue represents what is sometimes called the "frontier" in search algorithms.  It holds the set of unexplored nodes on the "edgeC" of the known tree.
	std::list<Node*> queue;

	/*
	the set of all visited states.  
	Note: we have to have this set in order to avoid cycles in our search tree. I will elaborate with an example.  Imagine that most of the puzzle remains in a certain state, but I decide to move one tile back and forth between two slots over and over, those moves are valid, but if I have made that move before while the puzzle is in this state, in this puzzle game, there is no reason to keep trying that move over and over.  
	
	If we allowed repeat moves, we would end up generating and having to search an infinite search tree, which would not be good :(, so, to avoid certain doom, we check if a puzzle state has already been generated before we add the corresponding node to the frontier queue.
	*/
	std::set<std::string> visitedStates;

	/*solutions
	this puzzle can have more than one solution. 
	If the chosen search type is optimal, the solutions will be sorted and the shortest 
	solution will be returned.
	Now, when I say solution, I am referring to the steps in order to solve the puzzle.  
	I am not referring to the state in which it is solved.  
	Also, keep in mind, as long as all the black tiles are on the left side, and all the white
	tiles are on the right side, it does not matter the order of the tiles.
	*/
	std::vector<std::vector<Node*>> solutions;

	//constructors
	Problem(std::string& state, std::string& searchType, bool evaluateCost);

	//search stuff
	void search();
	bool hasStateBeenVisited(const std::string& _state);
	static unsigned int g(const Node& n);
	static unsigned int h(const Node& n);
	
	//initialization stuff
	bool checkInitStringIsValid(std::string& inputString);
	std::string generateGoalState(std::string& inputString);
	SearchType determineSearchTypeFromString(const std::string& _string);
	void initNodeStorage(std::string& state);
	void checkCommandLineParams(std::string& state, std::string& searchTypeString);

	//making the path stuff
	std::string generateNextStateString(const std::string stateString, int selectedTile);
	void expand(Node* currentNode);
	Node* chooseNextToExpand();
	static unsigned int determineCost(const Node& currentNode);
	unsigned int determineCost(int tileToBeMoved, std::string& state);

	//compare functions
	static bool compareUCS(Node* node1, Node* node2);
	static bool compareGS(Node* node1, Node* node2);
	static bool compareAStar(Node* node1, Node* node2);

	void addToStorage(Node node);
	void storeSolution(Node* currentNode);
	void printSolution(std::vector<Node*>& path);
	void printBestSolution();
};

#endif