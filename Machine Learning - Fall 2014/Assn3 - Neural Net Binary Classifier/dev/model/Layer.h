#ifndef LAYER_H
#define LAYER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Neuron.h"

class Layer
{
private:
	std::string _name;

	unsigned int _numNeurons;

	std::vector<Neuron> _neurons;

	float _bias;


public:
	Layer();

	Layer(std::string name, int numNeurons, unsigned int numIncomingWeightsPerNeuron, unsigned int numOutgoingWeightsPerNeuron, float bias);

	Layer(const Layer& l);

	Layer& operator =(const Layer& l);

	friend std::ostream& operator<<(std::ostream& os, const Layer& n);

};
#endif
