#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "MDP.h"

float MDP::reward(State& state)
{
	return 0;
}

State MDP::transition(State& state, ActionVariable& actionVar)
{
	return *new State();
}

float MDP::utility(State& state)
{
	return 0;
}

ActionVariable* MDP::determineOptimalPolicy(unsigned int numIter)
{
	return 0;
}

ActionVariable* MDP::makePolicy()
{
	return 0;
}

ActionVariable MDP::Bellman(State& state)
{
	return *new ActionVariable();
}
