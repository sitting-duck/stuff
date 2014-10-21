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
}

HiddenNeuron::HiddenNeuron(const HiddenNeuron& hn)
{
}

HiddenNeuron& HiddenNeuron::operator =(const HiddenNeuron& hn)
{
	return *this;
}

inline std::ostream& operator<<(std::ostream& os, const HiddenNeuron& hn)
{
	std::cout << hn._name << std::endl;
	std::cout << "numIncomingWeights: " << hn._numIncomingWeights << std::endl;
	for(int i = 0; i < hn._incomingWeights.size(); i++){
		std::cout << hn._incomingWeights[i]->_val << " " ;
	}
	std::cout << "numOutgoingWeights: " << hn._numOutgoingWeights << std::endl;
	for(int i = 0; i < hn._outgoingWeights.size(); i++){
		std::cout << hn._outgoingWeights[i]->_val << " " ;
	}
	std::cout << std::endl;
	std::cout << "delta: " << hn._delta << std::endl;
	std::cout << "sumOfInputWeights: " << hn._sumOfInputWeights << std::endl;
	
	return os;
}
