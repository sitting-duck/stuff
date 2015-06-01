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
	Node* nodeStorage;
	unsigned int nodesInStorage;

	//this queue will hold the set of unvisited states. Each state must be checked that it has not yet been visited before it can be entered into this queue
	std::list<Node*> queue;

	//the set of all visited states
	std::set<std::string> visitedStates;

	//solutions
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