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

class State
{
	friend MDP_Parser;

private:
	float reward;

	float utility;

	std::vector<ActionVariable> actions;

};
#endif
