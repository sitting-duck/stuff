#ifndef WEIGHT_CONTROLLER_H
#define WEIGHT_CONTROLLER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

class WeightController
{
public:
	WeightController();

	float calcGradient(float incoming, float outputNeuronDelta);

	float calcNewWeight(float learningRate, float gradient, float momentum, float prevWeight);

	std::string genWeightName(unsigned int firstNeuron, char firstNeuronType, unsigned int secondNeuron, char secondNeuronType);

};
#endif
