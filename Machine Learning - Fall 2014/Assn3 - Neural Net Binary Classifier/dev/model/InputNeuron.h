#ifndef INPUT_NEURON_H
#define INPUT_NEURON_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Weight.h"

class InputNeuron
{
private:
	std::string _name;

	unsigned int _inputVal;

	unsigned int _numOutgoingWeights;

	std::vector<Weight*> _outgoingWeights;


public:
	InputNeuron();

	InputNeuron(std::string name, unsigned int numOutgoingWeights);

	InputNeuron(const InputNeuron& in);

	InputNeuron& operator =(const InputNeuron& in);

	friend std::ostream& operator<<(std::ostream& os, const InputNeuron& in);

};
#endif
