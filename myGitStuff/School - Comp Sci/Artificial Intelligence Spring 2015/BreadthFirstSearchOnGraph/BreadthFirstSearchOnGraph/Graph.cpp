
#include <list>
#include <iostream>
#include "Graph.h"

//Contsrtuctor
Graph::Graph(int _numVerts)
{
	this->numVerts = _numVerts;

	//create an adjecency list for each vertex
	adjacencyLists = new std::list<int>[_numVerts];

}

void Graph::addEdge(int vertex1, int vertex2)
{

	//the way that we add an edge is by stating that some vertex is adjecent to another vertex
	//we do that by adding one vertex to another vertex's adjecency list.
	//note that this is a directed graph, so is we are saying that vertex 2 is adjacent to vertex1
	//by adding vertex2 to vertex1's adjeacency list,	
	//then the edge is directed from vertex1 to vertex2.

	//first we do a check to make sure both vertex1 and vertex2 exist
	if(vertex1 > numVerts - 1 || vertex1 < 0)
	{
		std::cout << "Error::Graph::addEdge() : cannot add edge, vertex " << vertex1 << " does not exist" << std::endl;
		return;
	}
	if(vertex2 > numVerts - 1 || vertex2 < 0)
	{
		std::cout << "Error::Graph::addEdge() : cannot add edge, vertex " << vertex2 << " does not exist" << std::endl;
		return;
	}

	adjacencyLists[vertex1].push_back(vertex2);

}

//prints the breadth first traversal from the chosen starting vertex
void Graph::breadthFirstTraversal(int startingVertex)
{
	//mark all the vertices as not visited, they are al initialized to false
	bool* visited = new bool[this->numVerts]();

	//create a queue for BFS
	std::list<int> queue;

	//mark the starting node as visited and put it in the queue
	visited[startingVertex] = true;
	queue.push_back(startingVertex);

	//iter will be used to iterate through the adjacency list of a vertex
	std::list<int>::iterator iter;

	while(!queue.empty()){
		
		//grab the first vertex from the queue, assign it as the new starting vertex, and print it
		startingVertex = queue.front();
		std::cout << startingVertex << " ";
		queue.pop_front();

		//get all the adject vertices of the startingVertex,
		//if the adjacent has not been visited, then mark it visited and put it in the queue
		for(iter = adjacencyLists[startingVertex].begin(); iter != adjacencyLists[startingVertex].end(); ++iter)
		{
			if(!visited[*iter]) //if vert hasnt been visited
			{
				visited[*iter] = true; //set that it's been visited
				queue.push_back(*iter); //add it to the queue so that we can check all the adjacent verts for this vertex too
			}
		}
	}
}