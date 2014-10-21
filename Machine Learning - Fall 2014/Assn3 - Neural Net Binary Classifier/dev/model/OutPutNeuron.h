#ifndef OUTPUT_NEURON_H
#define OUTPUT_NEURON_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Weight.h"

class OutputNeuron
{
private:
	std::string _name;

	unsigned int _numIncomingWeights;

	std::vector<Weight*> _incomingWeights;

	float _delta;

	float _sumOfInputWeights;


public:
	OutputNeuron();

	OutputNeuron(std::string name, unsigned int numIncomingWeights);

	OutputNeuron(const OutputNeuron& on);

	OutputNeuron& operator =(const OutputNeuron& on);

	friend std::ostream& operator << (std::ostream& os, const OutputNeuron& on);

};
#endif
