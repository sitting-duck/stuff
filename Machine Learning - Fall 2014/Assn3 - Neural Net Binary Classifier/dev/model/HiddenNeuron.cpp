#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "HiddenNeuron.h"


HiddenNeuron::HiddenNeuron()
{
}

HiddenNeuron::HiddenNeuron(std::string name, unsigned int numIncomingWeights, unsigned int numOutgoingWeights, Net* net)
{
	_net = net;
	_name = name;
	_numIncomingWeights = numIncomingWeights;
	_numOutgoingWeights = numOutgoingWeights;
}

HiddenNeuron::HiddenNeuron(const HiddenNeuron& hn)
{
	_net = hn._net;
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
	_net = hn._net;
	_name = hn._name;
	_numIncomingWeights = hn._numIncomingWeights;
	_incomingWeights = hn._incomingWeights;
	_numOutgoingWeights = hn._numOutgoingWeights;
	_outgoingWeights = hn._outgoingWeights;
	_delta = hn._delta;
	_sumOfIncomingtWeights = hn._sumOfIncomingtWeights;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const HiddenNeuron& hn)
{
	std::cout << hn._name << std::endl;
	std::cout << "numIncomingWeights: " << hn._numIncomingWeights << std::endl;
	for(int i = 0; i < hn._incomingWeights.size(); i++){
		std::cout << hn._net->_weights[hn._incomingWeights[i]]._val << " " ;
	}
	std::cout << "numOutgoingWeights: " << hn._numOutgoingWeights << std::endl;
	for(int i = 0; i < hn._outgoingWeights.size(); i++){
		std::cout << hn._net->_weights[hn._outgoingWeights[i]]._val << " " ;
	}
	std::cout << std::endl;
	std::cout << "delta: " << hn._delta << std::endl;
	std::cout << "sumOfIncomingtWeights: " << hn._sumOfIncomingtWeights << std::endl;
	
	return os;
}
