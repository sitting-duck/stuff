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
	return 0;
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
