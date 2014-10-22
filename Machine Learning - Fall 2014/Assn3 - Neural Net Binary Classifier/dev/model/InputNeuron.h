#ifndef INPUT_NEURON_H
#define INPUT_NEURON_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

class Net;
class NetTeach;

class InputNeuron
{

	friend Net;
	friend NetTeach;

private:

	std::string _name;

	unsigned int _inputVal;

	unsigned int _numOutgoingWeights;

	//the indices of the weights pointed to by this neuron
	std::vector<unsigned int> _outgoingWeights;


public:
	InputNeuron();

	InputNeuron(std::string name, unsigned int numOutgoingWeights);

	InputNeuron(const InputNeuron& in);

	InputNeuron& operator =(const InputNeuron& in);

	friend std::ostream& operator<<(std::ostream& os, const InputNeuron& in);

};
#endif
