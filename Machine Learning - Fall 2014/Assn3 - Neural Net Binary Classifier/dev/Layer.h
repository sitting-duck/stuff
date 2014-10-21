#ifndef LAYER_H
#define LAYER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Neuron.h"
#include "std::string.h"
#include "const Layer.h"
#include "ostream.h"
#include "std : :ostream.h"
#include "std/vector.h"

class Layer
{
private:
	string _name : std:;

	unsigned int _numNeurons;

	std::vector<Neuron> _neurons : std:;

	float _bias;


public:
	Layer();

	Layer(std::string name, int numNeurons, unsigned int numIncomingWeightsPerNeuron, unsigned int numOutgoingWeightsPerNeuron, float bias);

	Layer(const Layer& l);

	Layer& operator =(const Layer& l);

	ostream& operator<<(std : :ostream& os, const Layer& n);

};
#endif
