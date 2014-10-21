#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "OutputNeuron.h"


OutputNeuron::OutputNeuron()
{
}

OutputNeuron::OutputNeuron(std::string name, unsigned int numIncomingWeights)
{
}

OutputNeuron::OutputNeuron(const OutputNeuron& on)
{
}

OutputNeuron& OutputNeuron::operator =(const OutputNeuron& on)
{
	return *this;
}

std::ostream& operator<<(std::ostream& os, const OutputNeuron& on)
{
	return os;
}
