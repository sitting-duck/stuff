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
#include "InputNeuron.h"
#include "HiddenNeuron.h"
#include "OutputNeuron.h"

class Net
{
private:
	float _learningRate;

	float _momentum;

	std::vector<InputNeuron> _inputLayer;

	std::vector<HiddenNeuron> _hiddenLayer;

	std::vector<OutputNeuron> _outputLayer;

	std::vector<Weight> _weights;

public:
	Net();

	Net(float learningRate, float momentum);

	Net(const Net& n);

	Net& operator =(const Net& n);

	friend std::ostream& operator << (std::ostream& os, const Net& n);

	friend std::ostream& operator << (std::ostream& os, std::vector<InputNeuron>& inv);

	friend std::ostream& operator << (std::ostream& os, const InputNeuron& in);

	friend std::ostream& operator << (std::ostream& os, const HiddenNeuron& hn);

	friend std::ostream& operator << (std::ostream& os, const OutputNeuron& on);

	void buildInputLayer(unsigned int numInputs);

};
#endif
