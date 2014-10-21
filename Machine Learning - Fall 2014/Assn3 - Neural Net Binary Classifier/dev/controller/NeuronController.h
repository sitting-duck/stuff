#ifndef NEURON_CONTROLLER_H
#define NEURON_CONTROLLER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Neuron.h"
#include "OutputNeuron.h"
#include "HiddenNeuron.h"

class NeuronController
{
public:
	NeuronController();

	float sumInputWeights(Neuron* neuron);

	float calcNeuronOutput(Neuron* neuron);

	float sigmoid(float in);

	float partialDeriv(float sum);

	float calcOutPutNeuronDelta(const OutputNeuron* on);

	float calcHiddenNeuronDelta(const HiddenNeuron* hn);

};
#endif
