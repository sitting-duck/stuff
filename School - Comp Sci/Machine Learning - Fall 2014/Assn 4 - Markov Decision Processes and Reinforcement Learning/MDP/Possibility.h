#ifndef POSSIBILITY_H
#define POSSIBILITY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

class MDP_Parser;
class MDP;

class Possibility
{

	friend MDP_Parser;
	friend MDP;

private:
	int stateChangeTo;

	float probability;

};
#endif
