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
	_name = name;
	_numOutgoingWeights = numOutgoingWeights;
}

InputNeuron::InputNeuron(const InputNeuron& in)
{
	_name = in._name;
	_inputVal = in._inputVal;
	_numOutgoingWeights = in._numOutgoingWeights;
	_outgoingWeights = in._outgoingWeights;
}

InputNeuron& InputNeuron::operator =(const InputNeuron& in)
{
	_name = in._name;
	_inputVal = in._inputVal;
	_numOutgoingWeights = in._numOutgoingWeights;
	_outgoingWeights = in._outgoingWeights;
	return *this;
}


