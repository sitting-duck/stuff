#ifndef NET_H
#define NET_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Layer.h"
#include "Weight.h"

class Net
{
private:
	float _learningRate;

	float _momentum;

	Layer _inputLayer;

	std::vector<Layer> _hiddenLayers;

	Layer _outputLayer;

	std::vector<Weight> _weights;


public:
	Net();

	Net(float learningRate, float momentum);

	Net(const Net& n);

	Net& operator =(const Net& n);

	friend std::ostream& operator<<(std::ostream& os, const Net& n);

};
#endif
