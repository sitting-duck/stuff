#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Net.h"
#include "InputNeuron.h"


Net::Net()
{
}

Net::Net(float learningRate, float momentum)
{
	_learningRate = learningRate;
	_momentum = momentum;
}

Net::Net(const Net& n)
{
	_learningRate = n._learningRate;
	_momentum = n._momentum;
	_inputLayer = n._inputLayer;
	_hiddenLayer = n._hiddenLayer;
	_outputLayer = n._outputLayer;
	_weights = n._weights;
}

Net& Net::operator =(const Net& n)
{
	_learningRate = n._learningRate;
	_momentum = n._momentum;
	_inputLayer = n._inputLayer;
	_hiddenLayer = n._hiddenLayer;
	_outputLayer = n._outputLayer;
	_weights = n._weights;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Net& n)
{
	std::cout << "input layer: " << std::endl;
	for(int i = 0; i < n._inputLayer.size(); i++){
		std::cout << n._inputLayer[i] << " ";
	}std::cout << std::endl;
	std::cout << "hidden layers: " << std::endl;
	for(int i = 0; i < n._hiddenLayer.size(); i++){
		std::cout << n._hiddenLayer[i] << " ";
	}std::cout << std::endl;
	std::cout << "output layer: " << std::endl;
	for(int i = 0; i < n._outputLayer.size(); i++){
		std::cout << n._outputLayer[i] << " ";
	}std::cout << std::endl;
	return os;
}

std::ostream& operator << (std::ostream& os, std::vector<InputNeuron>& inv){
	for(int i = 0; i < inv.size(); i++){
		std::cout << inv[i] << std::endl;
	}
	return os;
}

void Net::buildInputLayer(unsigned int numInputs){

	//and the number of outgoing weights it needs. The number of outgoing weights for this layer is based of the number of neurons in the next layer
		//we're going to use the half rule make num neurons in the hidden layer the mean of the num input + num out neurons over two
		//we add 0.5 at the end as a hacky workaround because round() is not supported by MSVC
	unsigned int numOutgoingWeights = (int)((numInputs + 1)/2 + 0.5);

	char numbuf[10] = {'\0'};
	std::string name = "i";
	std::string weightname = "i#_w#";
	//each neuron needs to be given a name. They are named as such: i0, i1, i2, etc.
	for(int i = 0; i < numInputs; i++){
		 itoa(i, numbuf, 10);
		 name.append(numbuf);
		 memset(numbuf, 0, 10);

		InputNeuron in = InputNeuron(name, numOutgoingWeights, this);
		
		//initialize all the weights to zero for this neuron
		for(int j = 0; j < numOutgoingWeights; j++){
		
			//create name. weight names are as such i1_w1 for outgoing weight 1 of input neuron 1
			weightname = name;
			weightname.append("_w");
			itoa(j, numbuf, 10);
			weightname.append(numbuf);
			memset(numbuf, 0, 10);

			//cerate weight
			Weight weight = Weight(weightname, 0.0f);
			//keep net global record of weight inside net
			_weights.push_back(weight);

			//and pass the neuron an index with which to reference it 
			in._outgoingWeights.push_back(_weights.size() - 1);
		}
		//add newly created input neuron to input layer
		_inputLayer.push_back(in);
		name = "i";
	}

	std::cout << _inputLayer << std::endl;
}