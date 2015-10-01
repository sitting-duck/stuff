#ifndef STATE_H
#define STATE_H

class State{

public:
	//the current state of the tile problem represented as a string
	std::string tileString;

	//the number of moves executed so far
	unsigned int numMoves;

	State(){}

	State(std::string& initString)
	{
		tileString = initString;
		numMoves = 0;
	}
};

#endif