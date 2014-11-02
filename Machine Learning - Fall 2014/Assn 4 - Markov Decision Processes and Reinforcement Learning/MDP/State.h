#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <vector>

#include "ActionVariable.h"

class MDP_Parser;
class MDP;

class State
{
	friend MDP_Parser;
	friend MDP;

private:
	float reward;

	float utility;

	std::vector<ActionVariable> actions;

};
#endif
