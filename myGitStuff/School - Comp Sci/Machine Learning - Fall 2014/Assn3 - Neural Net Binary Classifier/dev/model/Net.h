#ifndef NET_H
#define NET_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <cmath>
#include <stdlib.h>

#include "Weight.h"
//#include "InputNeuron.h"
//#include "HiddenNeuron.h"
//#include "OutputNeuron.h"
#include "WeightController.h"
#include "NeuronController.h"

class Net
{
public:
	float _learningRate;

	float _momentum;

	std::vector<InputNeuron> _inputLayer;

	std::vector<HiddenNeuron> _hiddenLayer;

	std::vector<OutputNeuron> _outputLayer;

	NeuronController neuronController;

	std::vector<Weight> _weights;

	WeightController weightController;

	Net();

	Net(float learningRate, float momentum);

	Net(const Net& n);

	Net& operator =(const Net& n);

	Weight findWeight(std::string& name);

	unsigned int findWeightIndex(std::string& name);

	float sumWeights(std::vector<unsigned int>& list);

	friend std::ostream& operator << (std::ostream& os, const Net& n);

	friend std::ostream& operator << (std::ostream& os, std::vector<InputNeuron>& inv);

	friend std::ostream& operator << (std::ostream& os, std::vector<HiddenNeuron>& hnv);

	friend std::ostream& operator << (std::ostream& os, std::vector<OutputNeuron>& onv);

	std::ostream& Net::printInputNeuron(std::ostream& os, const InputNeuron& in);

	std::ostream& Net::printHiddenNeuron(std::ostream& os, const HiddenNeuron& hn);

	std::ostream& Net::printOutputNeuron(std::ostream& os, const OutputNeuron& on);

	void buildInputLayer(unsigned int numInputs);

	void buildHiddenLayer();

	void buildOutputLayer();

};
#endif
