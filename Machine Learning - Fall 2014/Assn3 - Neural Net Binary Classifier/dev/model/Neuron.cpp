#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Neuron.h"


Neuron::Neuron()
{
}

Neuron::Neuron(std::string name)
{
}

Neuron::Neuron(const Neuron& n)
{
}

Neuron& Neuron::operator =(const Neuron& n)
{
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Neuron& n)
{
	std::cout << n._name << std::endl;
	return os;
}
