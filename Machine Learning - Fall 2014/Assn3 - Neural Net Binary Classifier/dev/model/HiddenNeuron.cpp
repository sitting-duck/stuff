#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "HiddenNeuron.h"


HiddenNeuron::HiddenNeuron()
{
}

HiddenNeuron::HiddenNeuron(std::string name, unsigned int numIncomingWeights, unsigned int numOutgoingWeights)
{
	_name = name;
	_numIncomingWeights = numIncomingWeights;
	_numOutgoingWeights = numOutgoingWeights;
}

HiddenNeuron::HiddenNeuron(const HiddenNeuron& hn)
{
	_name = hn._name;
	_numIncomingWeights = hn._numIncomingWeights;
	_incomingWeights = hn._incomingWeights;
	_numOutgoingWeights = hn._numOutgoingWeights;
	_outgoingWeights = hn._outgoingWeights;
	_delta = hn._delta;
	_sumOfIncomingtWeights = hn._sumOfIncomingtWeights;
}

HiddenNeuron& HiddenNeuron::operator =(const HiddenNeuron& hn)
{
	_name = hn._name;
	_numIncomingWeights = hn._numIncomingWeights;
	_incomingWeights = hn._incomingWeights;
	_numOutgoingWeights = hn._numOutgoingWeights;
	_outgoingWeights = hn._outgoingWeights;
	_delta = hn._delta;
	_sumOfIncomingtWeights = hn._sumOfIncomingtWeights;
	return *this;
}


