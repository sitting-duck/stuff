#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "NeuronController.h"


NeuronController::NeuronController()
{
}

float sumInputWeights(HiddenNeuron* neuron)
{
	return 0;
}

float sumInputWeights(OutputNeuron* neuron)
{
	return 0;
}

float calcNeuronOutput(InputNeuron* neuron)
{
	return 0;
}

float calcNeuronOutput(HiddenNeuron* neuron)
{
	return 0;
}

float calcNeuronOutput(OutputNeuron* neuron){
	return 0;
}

float NeuronController::sigmoid(float in)
{
	return (float)(1 / (1 + exp((-1)*in)));
}

float NeuronController::partialDeriv(float sum)
{
	return 0;
}

float NeuronController::calcOutPutNeuronDelta(const OutputNeuron* on)
{
	return 0;
}

float NeuronController::calcHiddenNeuronDelta(const HiddenNeuron* hn)
{
	return 0;
}

std::string NeuronController::genNeuronName(unsigned int index, char type){
	
	std::string neuronName;
	char numbuf[10] = {'\0'};

	std::string prefix;

	switch(type){
	case 'i':
		prefix = "i";
		break;
	case 'h':
		prefix = "h";
		break;
	case 'o':
		prefix = "o";
		break;
	default:
		std::cout << "Error: NeuronController::genNeuronName : invalid first neuron type" << std::endl;
	}

	neuronName.append(prefix);
	itoa(index, numbuf, 10);
	neuronName.append(numbuf);

	return neuronName;
}