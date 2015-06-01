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
	_name = name;
	_numIncomingWeights = numIncomingWeights;
}

OutputNeuron::OutputNeuron(const OutputNeuron& on)
{
	_name = on._name;
	_numIncomingWeights = on._numIncomingWeights;
	_incomingWeights = on._incomingWeights;
	_output = on._output;
	_delta = on._delta;
	_sumOfIncomingtWeights = on._sumOfIncomingtWeights;

}

OutputNeuron& OutputNeuron::operator =(const OutputNeuron& on)
{
	_name = on._name;
	_numIncomingWeights = on._numIncomingWeights;
	_incomingWeights = on._incomingWeights;
	_output = on._output;
	_delta = on._delta;
	_sumOfIncomingtWeights = on._sumOfIncomingtWeights;
	return *this;
}

