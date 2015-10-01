#include <cmath>
#include <ctgmath>
#include "Problem.h"

/*The goal state is the state in which the puzzle is solved.  For example, if we were given the 
puzzle, BWBxWBW, then the goal state for that puzzle would be BBBxWWW
*/
std::string Problem::goalState;

/*Indicates whether a moves have a measurable cost.  For the sake of this program, if the 
moves have cost, then the cost of each move is the slot distance for that move.
*/
bool Problem::hasCost;

/*
Problem constructor.  The problem class basically holds the state of the puzzle being solved and the search functions we use to solve the puzzle.

args:
state: indicates the initial state of the puzzle given from the file.

searchTypeString: indicates what type of search will be used to solve the puzzle.  The valid
search types are explained in the readme.

evaluateCost: indicates that each move in the solution of the puzzle has a measurable cost.
For this program we will measure cost as the slot distance between the initial and final positions of the tile.
*/
Problem::Problem(std::string& state, std::string& searchTypeString, bool evaluateCost)
{	
	//this bool indicates whether the user indicated the '-cost' flag in the command line
	hasCost = evaluateCost;

	//memory hack.  Try not to use more memory than we need to.
	initNodeStorage(state);

	//make sure the state and search type command args are valid, no typos, etc.
	checkCommandLineParams(state, searchTypeString);
		
	//generate the goal state string, will look like BxW, BBxWW, BBBxWWW, ect.
	goalState = generateGoalState(state);		

	//create the root node for the search tree
	root = Node(state, -1, NULL);
	
	//put the root into node storage
	nodeStorage[0] = root;
	
	//update the counter
	nodesInStorage = 1;
	
}

void Problem::search()
{

	//set current node to root, we start the search at the root
	Node* currentNode = &nodeStorage[0];
	
	//indicate that we have visited the root node of the search tree
	visitedStates.insert(root.state);

	//step 0 is the initial puzzle state
	std::cout << "Step 0: " << currentNode->state << std::endl;
	
	//this loop is essentially going to plow through the queue of nodes and process them
	while(1)
	{
		//check to see if the current state is the goal state
		if(currentNode->state.compare(goalState) == 0)
		{
			//greedy best first search quits as soon as it finds a solution instead of spanning
			//the entire search tree and returning the most optimal solution
			if(currentSearchType == GS)
			{
				//this search is not complete, so we quit here ( as soon as we find a solution )
				storeSolution(currentNode);
				printSolution(solutions.front());
				break;
			}
			else
			{
				//all other search types are complete so we continue searching until the queue finally empties out.
				storeSolution(currentNode);
			}
		}
		
		/*expanding a node: A node essentially represents a puzzle state.  From each puzzle state
		we can reach other adjacent puzzle states by making one move.  When we expand a node,
		we are generating all the adjacent states as nodes, and setting them as children of the 
		current node. In this way, we are storing all the possible puzzle paths as a tree.*/
		expand(currentNode);

		//if there are still nodes in the queue it means that some nodes have not yet
		//been processed.
		if(queue.size() != 0)
		{
			currentNode = chooseNextToExpand();
		}
		else
		{
			//complete search algorithms will end here because the queue is empty, meaning there is nothing else to search
			printBestSolution();
			break;
		}
		
	}
}

void Problem::expand(Node* currentNode)
{
	visitedStates.insert(currentNode->state);

	std::string newState;
	unsigned int cost;
	//generate the child nodes of the current Node and if they haven't been visited yet, place them in the queue
	for(unsigned int tileToBeMoved = 0; tileToBeMoved < currentNode->state.size(); tileToBeMoved++)
	{
		//in the state string if the char is not a space, then it is a tile, so we can move it

		if(currentNode->state[tileToBeMoved] != 'x')
		{
			//currentNode->action = tileToBeMoved;
			newState = generateNextStateString(currentNode->state, tileToBeMoved);			

			//if the state has not yet been visited, we can throw it in the frontier
			if(hasStateBeenVisited(newState) == false)
			{
				//create a node for this new state
				if(hasCost == true)
				{
					cost = determineCost(tileToBeMoved, newState);					
				}
				else
				{
					cost = 0;
				}
				Node newNode(newState, tileToBeMoved, currentNode, cost);
				addToStorage(newNode);
				visitedStates.insert(newState);

				//put a pointer to this newly made node in the queue
				queue.push_front(&nodeStorage[nodesInStorage - 1]);
				//std::cout << "added to queue : " << newNode.state << std::endl;
			}
		}
	}
}

Node* Problem::chooseNextToExpand()
{
	/*which node we choose to be expanded is entirely dependent on what type of search we are doing so we check for each search type. (instead of travelling down an actual tree, we are
	generating the nodes as we go, and simulating the way a certain search would go down a search
	tree by selecting the nodes from the queue in a certain order instead of actually hopping down a tree 
	*/
	
	Node* whichNode = NULL;
	switch(currentSearchType)
	{
	case BFS:
	/*
	by selecting the node closest to the back of the queue that means we added it earlier,
	which means it is higher up the tree.  The implication of this is that, we expand all
	the nodes on the 1st level, and then we expand all the nodes on the second level, and then
	the third level, exactly like a breadth first search.
	*/
		whichNode = queue.back();
		queue.pop_back();
		break;

	case DFS:
	/*
	by selecting the node at the front of the queue, that means we added it the most recently, 
	which means it is on the lowest current level of the tree.  The implication of this is that, each expansion is going to select the left-most or right-most (it depends on how we inserted the nodes into the queue) node and expand that node to create a new level each time.
	This is a depth first search because we are expanding all the way down until we cant anymore, and then we resume search at the last level with an unexpanded node.
	*/
		whichNode = queue.front();
		queue.pop_front();
		break;

	case UCS:
		queue.sort(Problem::compareUCS);
		whichNode = queue.front();
		queue.pop_front();
		break;
	case GS:
		queue.sort(Problem::compareGS);
		whichNode = queue.front();
		queue.pop_front();
		break;
	case ASTAR:
		queue.sort(Problem::compareAStar);
		whichNode = queue.front();
		queue.pop_front();
		break;
	}	
	return whichNode;
}

bool Problem::hasStateBeenVisited(const std::string& _state){
	bool hasStateBeenVisited = (visitedStates.find(_state) != visitedStates.end());
	return hasStateBeenVisited;
}

std::string Problem::generateNextStateString(std::string stateString, int selectedTile)
{
	char chosenTileChar;
	
	//grab the character for the tile at the specified location
	chosenTileChar = stateString[selectedTile];

	//find the index of the space
	size_t indexOfSpace;
	indexOfSpace = stateString.find_first_of('x');

	//place the chosen tile char in the spot where the space is
	stateString.replace(indexOfSpace, 1, 1, chosenTileChar);

	//place a space in the spot where the chosen tile was
	stateString.replace(selectedTile, 1, 1, 'x');

	//the string has now been updated for the tile move we did so we return it
	return stateString;
}

/*
returns true if the first node has a lower cumulative cost than the second node.

returns the cumulative cost down to this node.  Each move (equivalent to a level down the tree) has a cost of 1.
		
*/
bool Problem::compareUCS(Node* node1, Node* node2)
{
	return (g(*node1) < g(*node2)) ? true : false;
}

bool Problem::compareGS(Node* node1, Node* node2)
{
	return (h(*node1) < h(*node2)) ? true : false;
}

bool Problem::compareAStar(Node* node1, Node* node2)
{
	return ((g(*node1) + h(*node1)) < (g(*node2) + h(*node2))) ? true : false;
}

//for this problem g(n) will return the number of moves executed so far unless the user specifies '-cost' in the command line.
//In the case where the user enters the -cost flag, g(n) will calculate the cost of an action as the number of spaces a tile moves during an action
unsigned int Problem::g(const Node& n)
{
	
	Node currentNode(n);

	if(hasCost == false)
	{
		/*
		returns the cumulative cost down to this node.  Each move (equivalent to a level down the tree) has a cost of 1.
		*/
		unsigned int numMoves = 0;		
		while(currentNode.parent != NULL)
		{
			currentNode = *currentNode.parent;
			numMoves++;
		}
		return numMoves;
	}
	else
	{
		/*
		returns the numbers of slots a tile will travel in the given move.
		Argument 1 is the node representing the initial puzzle state, 
		argument 1 is the node representing the final puzzle state, 
		the difference between the two states is used to calculate the cost of the move.
		*/
		unsigned int totalCost = 0;
		while(currentNode.parent != NULL)
		{
			currentNode = *currentNode.parent;
			totalCost += currentNode.cost;
		}
		return totalCost;
	}
	
}

/*
returns the number of tiles out of place.
The number of tiles out of place is the number of tiles in the current state that are different from the solution state.
*/
unsigned int Problem::h(const Node& n){
	//measure and return number of tiles out of place
	unsigned int numTilesOutOfPlace = 0;

	for(unsigned int i = 0; i < goalState.size(); i++)
	{
		if(n.state[i] != goalState[i])
		{
			numTilesOutOfPlace++;
		}
	}

	return numTilesOutOfPlace;

}

unsigned int Problem::determineCost(const Node& currentNode)
{
	int indexOfSpace = currentNode.state.find_first_of("x");
	int indexOfTileToBeMoved = currentNode.action - 1;  //correct for off by one error

	return std::abs(indexOfSpace - indexOfTileToBeMoved);
}

unsigned int Problem::determineCost(int tileToBeMoved, std::string& state)
{
	int indexOfSpace = state.find_first_of("x");
	return std::abs(indexOfSpace - tileToBeMoved);
}

void Problem::addToStorage(Node node)
{
	//if there is no more space in the array to add nodes we will grab more memory
	if(nodesInStorage % chunkSize == 0)
	{
		std::cout << "we added another chunk to the storage array. Nodes in storage is " << nodesInStorage << std::endl;
		Node* tempNodeStorage = new Node[nodesInStorage + chunkSize];

		for(unsigned int i = 0; i < nodesInStorage; i++)
		{
			tempNodeStorage[i] = nodeStorage[i];
		}
		delete[] nodeStorage;

		nodeStorage = new Node[nodesInStorage + chunkSize];
		for(unsigned int i = 0; i < nodesInStorage; i++)
		{
			nodeStorage[i] = tempNodeStorage[i];
		}
		delete[] tempNodeStorage;
	}

	nodeStorage[nodesInStorage] = node;
	nodesInStorage++;
}

void Problem::storeSolution(Node* currentNode)
{
	//this algo is going to back trace all the way up to the root, adn then add that path to the list of solutions
	
	std::vector<Node*> path;
	while(currentNode->parent != NULL)
	{
		path.push_back(currentNode);
		currentNode = currentNode->parent;
	}
	solutions.push_back(path);
}

void Problem::printSolution(std::vector<Node*>& path)
{
	unsigned int step = 1;
	for(int index = path.size() - 1; index >= 0; index--)
	{
		std::cout << "Step " << step << ": move " << path[index]->action + 1 << " " << path[index]->state << std::endl;
		step++;
	}
}

void Problem::printBestSolution()
{
	unsigned int currentBestSolutionIndex = 0;
	unsigned int currentBestSolutionSize = 99999999;
	unsigned int currentSolutionSize = 0;

	for(unsigned int solutionIndex = 0; solutionIndex < solutions.size(); solutionIndex++)
	{
		currentSolutionSize = solutions[solutionIndex].size();

		if(currentSolutionSize < currentBestSolutionSize)
		{
			currentBestSolutionSize = currentSolutionSize;
			currentBestSolutionIndex = solutionIndex;
		}
	}

	printSolution(solutions[currentBestSolutionIndex]);
}

