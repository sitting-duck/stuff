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

Weight Net::findWeight(std::string& name){
	for(int i = 0; i < _weights.size(); i++){
		if(_weights[i]._name == name){
			return _weights[i];
		}
	}
}

unsigned int Net::findWeightIndex(std::string& name){
	for(int i = 0; i < _weights.size(); i++){
		if(_weights[i]._name == name){
			return i;
		}
	}
}

float Net::sumWeights(std::vector<unsigned int>& list){
	float sum = 0;
	for(int i = 0; i < list.size(); i++){
		sum += _weights[list[i]]._val;
	}
	return sum;
}

void Net::buildInputLayer(unsigned int numInputs){

	//and the number of outgoing weights it needs. The number of outgoing weights for this layer is based of the number of neurons in the next layer
		//we're going to use the half rule make num neurons in the hidden layer the mean of the num input + num out neurons over two
		//we add 0.5 at the end as a hacky workaround because round() is not supported by MSVC
	unsigned int numOutgoingWeights = (int)((numInputs + 1)/2 + 0.5);
	
	//declaring these outside the loop so they don't get regenerated over and over
	std::string neuronName;
	std::string weightname;

	//each neuron needs to be given a name. They are named as such: i0, i1, i2, etc.
	for(int i = 0; i < numInputs; i++){
		 std::string neuronName = neuronController.genNeuronName(i, 'i');

		InputNeuron in = InputNeuron(neuronName, numOutgoingWeights);
		
		//initialize all the weights to zero for this neuron
		//weights are always init to zero for every neuron
		for(int j = 0; j < numOutgoingWeights; j++){
		
			//create name. weight names are as such w_i1h1 for the weight connecting i1 to h1
			weightname = weightController.genWeightName(i, 'i', j, 'h');

			//cerate weight
			Weight weight = Weight(weightname, 0.0f);
			//keep net global record of weight inside net
			_weights.push_back(weight);

			//and pass the neuron an index with which to reference it 
			in._outgoingWeights.push_back(_weights.size() - 1);
		}
		//add newly created input neuron to input layer
		_inputLayer.push_back(in);
	}	
}

void Net::buildHiddenLayer(){
	unsigned int numHiddenNeurons = (int)((_inputLayer.size() + 1)/2 + 0.5);

	
	std::string neuronName;
	std::string weightname;
	
	for(unsigned int i = 0; i < numHiddenNeurons; i++){
		
		//create neuron name
		neuronName = neuronController.genNeuronName(i, 'h');
		HiddenNeuron hn = HiddenNeuron(neuronName, _inputLayer.size(), 1);

		//create weight name
		weightname = weightController.genWeightName(i, 'h', 1, 'o');
		Weight outgoingWeight = Weight(weightname, 0.0f);

		//now we have to figure out the indices of the incoming weights for this hidden neuron
		//well quite simply, every neuron in the previous layer points to this neuron		
		for(unsigned int j = 0; j < hn._numIncomingWeights; j++){
			
			weightname = weightController.genWeightName(j, 'i', i, 'h');
			hn._incomingWeights.push_back(findWeightIndex(weightname));
		}
		hn._sumOfIncomingtWeights = sumWeights(hn._incomingWeights);

		//keep net global record of weight inside net
		_weights.push_back(outgoingWeight);

		//and pass the neuron an index with which to reference it 
		hn._outgoingWeights.push_back(_weights.size() - 1);

		//add this neuron to the net global hidden layer neurons list
		_hiddenLayer.push_back(hn);
	}	
}

void Net::buildOutputLayer(){
	std::string neuronName;
	//create neuron name
	neuronName = neuronController.genNeuronName(1, 'o');

	OutputNeuron on = OutputNeuron(neuronName, _hiddenLayer.size());

	std::string weightname;
	//now we have to figure out the indices of the incoming weights for this hidden neuron
	//well quite simply, every neuron in the previous layer points to this neuron
	for(unsigned int j = 0; j < on._numIncomingWeights; j++){
			
		weightname = weightController.genWeightName(j, 'h', 1, 'o');
		on._incomingWeights.push_back(findWeightIndex(weightname));
	}
	on._sumOfIncomingtWeights = sumWeights(on._incomingWeights);

	_outputLayer.push_back(on);
}