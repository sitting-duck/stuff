#include <iostream>
#include "Problem.h"

void Problem::initNodeStorage(std::string& state)
{
	//memory hack: BFS is so demanding for memory that we need to conserve memory when we can
	switch(state.size())
	{
	case 3:
		chunkSize = 100;
		break;
	case 5:
		chunkSize = 100;
		break;
	case 7:
		chunkSize = 1000;
		break;
	case 9:
		chunkSize = 1000;
		break;
	case 11:
		chunkSize = 10000;
		break;
	case 13:
		chunkSize = 20000;
		break;
	default:
		chunkSize = 1000;
	}

	//initialize node storage
	nodeStorage = (Node*)new Node[chunkSize];
}

void Problem::checkCommandLineParams(std::string& state, std::string& searchTypeString)
{
	//check if the given tile config string is valid
	if(!checkInitStringIsValid(state))
	{
		std::cout << "Error: Initial tile configuration given in file is not valid." << std::endl;
		exit(1);
	}

	//figure out if we've been given a valid search type string
	SearchType searchType = determineSearchTypeFromString(searchTypeString);

	if(searchType == -1)
	{
		exit(1);
	}
	else
	{
		currentSearchType = searchType;
	}
}

bool Problem::checkInitStringIsValid(std::string& inputString){

	//calculate number of black and white tiles from the string
	unsigned int numBlack = 0;
	unsigned int numWhite = 0;

	for(unsigned int i = 0; i < inputString.size(); i++)
	{
		if(inputString[i] == 'b' || inputString[i] == 'B'){ numBlack++; }
		if(inputString[i] == 'w' || inputString[i] == 'W'){ numWhite++; }
	}

	//a valid string must be less than 14 characters
	if(inputString.size() > 13){ return false; }

	//a valid string must have an odd number of characters
	else if(inputString.size() % 2 == 0){ return false; }

	//a valid string can only contain the characters b, B, w, W and x
	else if(inputString.find_first_not_of("bBwWx") != std::string::npos){ return false; }

	//a valid string must contain a space
	else if(inputString.find_first_of("x") == std::string::npos){ return false; }

	//a valid string must has the same number of black and white tiles
	else if(numBlack != numWhite){ return false; }
	
	else{ return true; }
}

std::string Problem::generateGoalState(std::string& inputString){

	unsigned int numTileOfOneColor = (inputString.size() - 1) / 2;

	std::string goalString;

	//the tiles must contain all back tiles to the left of the space
	for(unsigned int i = 0; i < numTileOfOneColor; i++){
		goalString.append("B");
	}

	//a space in the middle
	goalString.append("x");

	//and all white tiles to the right of the space
	for(unsigned int i = 0; i < numTileOfOneColor; i++){
		goalString.append("W");
	}

	return goalString;
}

Problem::SearchType Problem::determineSearchTypeFromString(const std::string& _string)
{
	if(_string.compare("BFS") == 0){ return BFS; }
	else if(_string.compare("DFS") == 0){ return DFS; }
	else if(_string.compare("UCS") == 0){ return UCS; }
	else if(_string.compare("GS") == 0){ return GS; }
	else if(_string.compare("A-star") == 0){ return ASTAR; }
	else
	{
		std::cout << "Error: invalid search type : " << _string << " entered. Can only enter BFS, DFS, UCS, GS, or A-star as search type" << std::endl;
		return NOT_A_SEARCH_TYPE;
	}
}