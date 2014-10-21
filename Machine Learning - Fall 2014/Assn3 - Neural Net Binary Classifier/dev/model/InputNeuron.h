#ifndef INPUT_NEURON_H
#define INPUT_NEURON_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Weight.h"
#include "Net.h"

class Net;

class InputNeuron
{

	friend Net;

private:
	//handle to net
	Net* _net;

	std::string _name;

	unsigned int _inputVal;

	unsigned int _numOutgoingWeights;

	//the indices of the weights pointed to by this neuron
	std::vector<unsigned int> _outgoingWeights;


public:
	InputNeuron();

	InputNeuron(std::string name, unsigned int numOutgoingWeights, Net* net);

	InputNeuron(const InputNeuron& in);

	InputNeuron& operator =(const InputNeuron& in);

	friend std::ostream& operator<<(std::ostream& os, const InputNeuron& in);

};
#endif
