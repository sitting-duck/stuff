
//taken from http://www.geeksforgeeks.org/breadth-first-traversal-for-a-graph/
//changed up and adapted the code as I felt fit

#include <iostream>
#include "Graph.h"

using namespace std;

void main()
{
	//let's do some testing
	

	//first lets make the graph object with 5 vertices
	Graph graph(5);

	//at this point, no vertices are adjacent to eachother
	//let's make vert1 adj to vert2, vert2 adj to vert3 and so on,

	graph.addEdge(0, 1);
	graph.addEdge(1, 2);
	graph.addEdge(2, 3);
	graph.addEdge(3, 4);

	//notice what happens when we try to add an edge to a vertex that does not exist
	//note: numbering of vertices starts at 0 and not 1.  So with 5 verts, the last vet will have index 4.
	graph.addEdge(4, 5);

	//now lets start testing the breadth first traversal, let's make the search start at vertex 0
	graph.breadthFirstTraversal(0);
}