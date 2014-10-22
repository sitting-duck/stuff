#ifndef OUTPUT_NEURON_H
#define OUTPUT_NEURON_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

class Weight;
class Net;

class OutputNeuron
{
	friend Weight;
	friend Net;

private:

	std::string _name;

	unsigned int _numIncomingWeights;

	//the indices of the weights pointed to by this neuron
	std::vector<unsigned int> _incomingWeights;

	float _output;

	float _delta;

	float _sumOfIncomingtWeights;


public:
	OutputNeuron();

	OutputNeuron(std::string name, unsigned int numIncomingWeights);

	OutputNeuron(const OutputNeuron& on);

	OutputNeuron& operator =(const OutputNeuron& on);

	friend std::ostream& operator << (std::ostream& os, const OutputNeuron& on);

};
#endif
