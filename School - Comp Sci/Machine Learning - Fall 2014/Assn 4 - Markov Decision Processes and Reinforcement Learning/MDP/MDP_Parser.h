#ifndef M_D_P__PARSER_H
#define M_D_P__PARSER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <vector>

#include "State.h"
#include "ActionVariable.h"
#include "Possibility.h"
#include "MDP.h"

class MDP_Parser
{
private:
	std::vector<State> states;

	float gamma;


public:
	State getNextState(std::string& line);

	void getAndSetNextActionVariablePossibility(State& state, std::string& actionNode);

	MDP getStuff(const char* filename);

	//utils
	float extractNumberFromToken(std::string token); 

};
#endif
