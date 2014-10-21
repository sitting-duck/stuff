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
	std::cout << on._name << std::endl;
	std::cout << "numIncomingWeights: " << on._numIncomingWeights << std::endl;
	for(int i = 0; i < on._incomingWeights.size(); i++){
		std::cout << on._incomingWeights[i]->_val << " " ;
	}
	std::cout << std::endl;
	std::cout << "delta: " << on._delta << std::endl;
	std::cout << "sumOfInputWeights: " << on._sumOfInputWeights << std::endl;

	return os;
}
