#ifndef INPUT_NEURON_H
#define INPUT_NEURON_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Weight.h"
#include "std::string.h"
#include "const InputNeuron.h"
#include "ostream.h"
#include "std : :ostream.h"
#include "const intputNeuron.h"
#include "std/vector.h"

class InputNeuron
{
private:
	string _name : std:;

	unsigned int _inputVal;

	unsigned int _numOutgoingWeights;

	std::vector<Weight*,allocator<T>> _outgoingWeights : std:;


public:
	InputNeuron();

	InputNeuron(std::string name, unsigned int numOutgoingWeights);

	InputNeuron(const InputNeuron& in);

	InputNeuron& operator =(const InputNeuron& in);

	ostream& operator<<(std : :ostream& os, const intputNeuron& in);

};
#endif
