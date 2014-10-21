#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Layer.h"


Layer::Layer()
{
}

Layer::Layer(std::string name, int numNeurons, unsigned int numIncomingWeightsPerNeuron, unsigned int numOutgoingWeightsPerNeuron, float bias)
{
}

Layer::Layer(const Layer& l)
{
}

Layer& Layer::operator =(const Layer& l)
{
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Layer& n)
{
	return os;
}
