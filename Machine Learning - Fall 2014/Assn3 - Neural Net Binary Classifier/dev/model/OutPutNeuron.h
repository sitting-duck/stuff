#ifndef OUTPUT_NEURON_H
#define OUTPUT_NEURON_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Weight.h"
#include "Net.h"

class Weight;

class OutputNeuron
{
	friend Weight;

private:
	//handle to net
	Net* _net;

	std::string _name;

	unsigned int _numIncomingWeights;

	//the indices of the weights pointed to by this neuron
	std::vector<unsigned int> _incomingWeights;

	float _delta;

	float _sumOfIncomingtWeights;


public:
	OutputNeuron();

	OutputNeuron(std::string name, unsigned int numIncomingWeights, Net* net);

	OutputNeuron(const OutputNeuron& on);

	OutputNeuron& operator =(const OutputNeuron& on);

	friend std::ostream& operator << (std::ostream& os, const OutputNeuron& on);

};
#endif
