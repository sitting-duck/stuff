
#ifndef GRAPH_H
#define GRAPH_H

#include <list>

//This class represents a directed graph using adjecency list representation
class Graph
{

	int numVerts;

	//pointer to an array containing adjacency lists
	std::list<int> *adjacencyLists;

public:

	//Constructor
	Graph(int _numVerts);

	void addEdge(int vertex1, int vertex2);

	//prints the breadth first traversal from the chosen starting vertex
	void breadthFirstTraversal(int startingVertex);

};

#endif