#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "InputNeuron.h"


InputNeuron::InputNeuron()
{
}

InputNeuron::InputNeuron(std::string name, unsigned int numOutgoingWeights)
{
}

InputNeuron::InputNeuron(const InputNeuron& in)
{
}

InputNeuron& InputNeuron::operator =(const InputNeuron& in)
{
	return *this;
}

std::ostream& operator << (std::ostream& os, const InputNeuron& in)
{
	return os;
}
