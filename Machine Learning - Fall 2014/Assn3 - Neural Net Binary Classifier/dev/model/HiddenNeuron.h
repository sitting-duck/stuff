#ifndef HIDDEN_NEURON_H
#define HIDDEN_NEURON_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Weight.h"

class HiddenNeuron
{
private:
	std::string _name;

	unsigned int _numIncomingWeights;

	std::vector<Weight*> _incomingWeights;

	unsigned int _numOutgoingWeights;

	std::vector<Weight*> _outgoingWeights;

	float _delta;

	float _sumOfInputWeights;


public:
	HiddenNeuron();

	HiddenNeuron(std::string name, unsigned int numIncomingWeights, unsigned int numOutgoingWeights);

	HiddenNeuron(const HiddenNeuron& hn);

	HiddenNeuron& operator =(const HiddenNeuron& hn);

	friend std::ostream& operator<<(std::ostream& os, const HiddenNeuron& hn);

};
#endif
