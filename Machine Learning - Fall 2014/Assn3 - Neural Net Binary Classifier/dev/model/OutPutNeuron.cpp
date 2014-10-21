#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "OutputNeuron.h"


OutputNeuron::OutputNeuron()
{
}

OutputNeuron::OutputNeuron(std::string name, unsigned int numIncomingWeights, Net* net)
{
	_net = net;
	_name = name;
	_numIncomingWeights = numIncomingWeights;

	//TODO: calc _sumOfIncomingWeights
}

OutputNeuron::OutputNeuron(const OutputNeuron& on)
{
	_net = on._net;
	_name = on._name;
	_numIncomingWeights = on._numIncomingWeights;
	_incomingWeights = on._incomingWeights;
	_delta = on._delta;
	_sumOfIncomingtWeights = on._sumOfIncomingtWeights;

}

OutputNeuron& OutputNeuron::operator =(const OutputNeuron& on)
{
	_net = on._net;
	_name = on._name;
	_numIncomingWeights = on._numIncomingWeights;
	_incomingWeights = on._incomingWeights;
	_delta = on._delta;
	_sumOfIncomingtWeights = on._sumOfIncomingtWeights;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const OutputNeuron& on)
{
	std::cout << on._name << std::endl;
	std::cout << "numIncomingWeights: " << on._numIncomingWeights << std::endl;
	for(int i = 0; i < on._incomingWeights.size(); i++){
		std::cout << on._net->_weights[on._incomingWeights[i]]._val << " " ;
	}
	std::cout << std::endl;
	std::cout << "delta: " << on._delta << std::endl;
	std::cout << "sumOfIncomingtWeights: " << on._sumOfIncomingtWeights << std::endl;

	return os;
}
