#ifndef HIDDEN_NEURON_H
#define HIDDEN_NEURON_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Weight.h"
#include "std::string.h"
#include "const HiddenNeuron.h"
#include "ostream.h"
#include "std : :ostream.h"
#include "std/vector.h"

class HiddenNeuron
{
private:
	string _name : std:;

	unsigned int _numIncomingWeights;

	std::vector<Weight*,allocator<T>><T>> _incomingWeights : std:;

	unsigned int _numOutgoingWeights;

	std::vector<Weight*,allocator<T>><T>> _outgoingWeights : std:;

	float _delta;

	float _sumOfInputWeights;


public:
	HiddenNeuron();

	HiddenNeuron(std::string name, unsigned int numIncomingWeights, unsigned int numOutgoingWeights);

	HiddenNeuron(const HiddenNeuron& hn);

	HiddenNeuron& operator =(const HiddenNeuron& hn);

	ostream& operator<<(std : :ostream& os, const HiddenNeuron& hn);

};
#endif
