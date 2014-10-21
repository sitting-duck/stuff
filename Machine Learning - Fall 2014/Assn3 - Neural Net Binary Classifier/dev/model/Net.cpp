#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Net.h"


Net::Net()
{
}

Net::Net(float learningRate, float momentum)
{
}

Net::Net(const Net& n)
{
}

Net& Net::operator =(const Net& n)
{
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Net& n)
{
	std::cout << "input layer: " << std::endl;
	std::cout << n._inputLayer << std::endl;
	std::cout << "hidden layers: " << std::endl;
	for(int i = 0; i < n._hiddenLayers.size(); i++){
		std::cout << n._hiddenLayers[i] << std::endl;
	}
	std::cout << "output layer: " << std::endl;
	std::cout << n._outputLayer << std::endl;
	return os;
}
