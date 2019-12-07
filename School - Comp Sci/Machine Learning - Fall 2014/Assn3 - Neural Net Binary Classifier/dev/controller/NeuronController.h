#ifndef NEURON_CONTROLLER_H
#define NEURON_CONTROLLER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "InputNeuron.h"
#include "OutputNeuron.h"
#include "HiddenNeuron.h"

class NeuronController
{
public:
	NeuronController();

	float sumInputWeights(HiddenNeuron* neuron);

	float sumInputWeights(OutputNeuron* neuron);

	float calcNeuronOutput(InputNeuron* neuron);

	float calcNeuronOutput(HiddenNeuron* neuron);

	float calcNeuronOutput(OutputNeuron* neuron);

	float sigmoid(float in);

	float partialDeriv(float sum);

	float calcOutPutNeuronDelta(const OutputNeuron* on);

	float calcHiddenNeuronDelta(const HiddenNeuron* hn);

	std::string genNeuronName(unsigned int index, char type);


};
#endif
