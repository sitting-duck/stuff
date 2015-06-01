#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "JointWeight.h"

JointWeight::JointWeight()
{
}

JointWeight::JointWeight(int _jointIndex, float _weight){
	index = _jointIndex;
	weight = _weight;
}

void JointWeight::setWeight(float _weight)
{
}

float JointWeight::getWeight()
{
	return 0;
}

void JointWeight::printJointWeight()
{
}
