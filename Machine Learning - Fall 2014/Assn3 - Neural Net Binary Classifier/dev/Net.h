#ifndef NET_H
#define NET_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Layer.h"
#include "Weight.h"
#include "const Net.h"
#include "ostream.h"
#include "std : :ostream.h"
#include "std/vector.h"

class Net
{
private:
	float _learningRate;

	float _momentum;

	Layer _inputLayer;

	std::vector<Layer> _hiddenLayers : std:;

	Layer _outputLayer;

	std::vector<Weight> _weights : std:;


public:
	Net();

	Net(float learningRate, float momentum);

	Net(const Net& n);

	Net& operator =(const Net& n);

	ostream& operator<<(std : :ostream& os, const Net& n);

};
#endif
