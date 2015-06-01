#include <cmath>
#include <ctgmath>
#include "Problem.h"

std::string Problem::goalState;
bool Problem::hasCost;

Problem::Problem(std::string& state, std::string& searchTypeString, bool evaluateCost)
{	
	//this bool indicates whether the user indicated the '-cost' flag in the command line
	hasCost = evaluateCost;

	initNodeStorage(state);

	checkCommandLineParams(state, searchTypeString);
		
	//generate the goal state string, will look like BxW, BBxWW, BBBxWWW, ect.
	goalState = generateGoalState(state);		

	root = Node(state, -1, NULL);
	nodeStorage[0] = root;
	nodesInStorage = 1;
	
}

void Problem::search()
{

	//set current node to root
	Node* currentNode = &nodeStorage[0];
	visitedStates.insert(root.state);

	std::cout << "Step 0: " << currentNode->state << std::endl;
	
	while(1)
	{
		//check to see if the current state is the goal state
		if(currentNode->state.compare(goalState) == 0)
		{
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
				
		expand(currentNode);

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
	//which node we choose to be expanded is entirely dependent on what type of search we are doing so we check for each search type

	Node* whichNode = NULL;
	switch(currentSearchType)
	{
	case BFS:
		whichNode = queue.back();
		queue.pop_back();
		break;

	case DFS:
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
unsigned int Problem::g(const Node& n){
	
	Node currentNode(n);

	if(hasCost == false)
	{
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
		unsigned int totalCost = 0;
		while(currentNode.parent != NULL)
		{
			currentNode = *currentNode.parent;
			totalCost += currentNode.cost;
		}
		return totalCost;
	}
	
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

