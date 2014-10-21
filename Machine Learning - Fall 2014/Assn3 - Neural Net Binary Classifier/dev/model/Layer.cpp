#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Layer.h"


Layer::Layer()
{
}

Layer::Layer(std::string name, int numNeurons, unsigned int numIncomingWeightsPerNeuron, unsigned int numOutgoingWeightsPerNeuron, float bias)
{
}

Layer::Layer(const Layer& l)
{
}

Layer& Layer::operator =(const Layer& l)
{
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Layer& n)
{
	std::cout << n._name << std::endl;
	std::cout << "num neurons: " << n._numNeurons << std::endl;
	for(int i = 0; i < n._neurons.size(); i++){
		std::cout << n._neurons[i] << std::endl;
	}
	std::cout << "bias: " << n._bias << std::endl;
	return os;
}
