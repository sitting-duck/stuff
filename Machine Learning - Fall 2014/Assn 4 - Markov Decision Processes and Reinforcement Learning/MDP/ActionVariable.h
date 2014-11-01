#ifndef ACTION_VARIABLE_H
#define ACTION_VARIABLE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <vector>

#include "Possibility.h"

class MDP_Parser;

class ActionVariable
{

	friend MDP_Parser;

private:
	std::vector<Possibility> possibilities;

};
#endif
