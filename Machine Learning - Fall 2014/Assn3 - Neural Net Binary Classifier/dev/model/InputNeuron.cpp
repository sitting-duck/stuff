#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "InputNeuron.h"


InputNeuron::InputNeuron()
{
}

InputNeuron::InputNeuron(std::string name, unsigned int numOutgoingWeights, Net* net)
{
	_net = net;
	_name = name;
	_numOutgoingWeights = numOutgoingWeights;
}

InputNeuron::InputNeuron(const InputNeuron& in)
{
	_net = in._net;
	_name = in._name;
	_numOutgoingWeights = in._numOutgoingWeights;
	_outgoingWeights = in._outgoingWeights;
}

InputNeuron& InputNeuron::operator =(const InputNeuron& in)
{
	_net = in._net;
	_name = in._name;
	_numOutgoingWeights = in._numOutgoingWeights;
	_outgoingWeights = in._outgoingWeights;
	return *this;
}

std::ostream& operator << (std::ostream& os, const InputNeuron& in)
{
	std::cout << in._name << std::endl;
	std::cout << "input val: " << in._inputVal << std::endl;
	std::cout << "numOutgoingWeights: " << in._numOutgoingWeights << std::endl;
	for(int i = 0; i < in._outgoingWeights.size(); i++){
		std::cout << in._net->_weights[in._outgoingWeights[i]]._val << " " ;
	}
	std::cout << std::endl;
	
	return os;
}
