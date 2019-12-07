 #include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "NetTeach.h"


NetTeach::NetTeach()
{
}

NetTeach::NetTeach(float learningRate, unsigned int numIter)
{
	_learningRate = learningRate;
	_numTotalIter = numIter;
}

NetTeach::NetTeach(const NetTeach& nt)
{
	_learningRate = nt._learningRate;
	_numTotalIter = nt._numTotalIter;
}

NetTeach& NetTeach::operator =(const NetTeach& nt)
{
	_learningRate = nt._learningRate;
	_numTotalIter = nt._numTotalIter;
	return *this;
}

std::vector<Instance> NetTeach::getExamplesFromFile(std::string& filename)
{
	//open the file
	std::ifstream filestream;
	filestream.open(filename);

	std::string line;
	if(filestream.is_open()){

		//grab the first line, it contains the attribute names
		getline(filestream, line);

		//delimiters include tab and space
		const char* delim = " \t";
		
		//placeholders for tokenizing the current line, these keep the tokenizer moving forward so we don't acknowledge the same space more than once
		size_t prev = 0;
		size_t next = 0;

		if(_attrNames.size() != 0){
			_attrNames.clear();
		}
		while((next = line.find_first_of(delim, prev)) != std::string::npos){
			
				//if the token we got is not an empty string, add it to _attrNames
				if(next - prev != 0){
					_attrNames.push_back(line.substr(prev, next - prev));
				}
				//update the placeholder
				prev = next + 1;
			}

			//reset some variables for the next loop around
			prev = 0; next = 0;

		//gonna grab these from the file. The rest of the lines will contain attibute and class values
		unsigned int numValues = 0;
		std::vector<unsigned int> values;
		unsigned int classVal;

		//examples container that we will return
		std::vector<Instance> examples;

		while(getline(filestream, line)){
			while((next = line.find_first_of(delim, prev)) != std::string::npos){
			
				//if the token we got is not an empty string, add it to values
				if(next - prev != 0){
					values.push_back(atoi(line.substr(prev, next - prev).c_str()));
				}
				//update the placeholder
				prev = next + 1;
			}

			//grab the last token and assign it to classVal
			if(prev < line.size()){
				classVal = atoi(line.substr(prev, next - prev).c_str());
			}

			numValues = values.size();

			//create the Instance object, one line equals one instance
			Instance instance(numValues, values, classVal);

			//add it to examples container
			examples.push_back(instance);

			//reset some variables for the next loop around
			prev = 0; next = 0;
			values.clear();
		}
		filestream.close();


		return examples;
	
	}else{
	
		std::cout << "unable to open file " << filename << std::endl;
		exit(1);
	
	}
}

void NetTeach::setTrainingExamples(std::vector<Instance> trainex){
	_trainex = trainex;
}

void NetTeach::setTestingExamples(std::vector<Instance> testex){
	_testex = testex;
}

float NetTeach::teach(Net& net, unsigned int iterationNum)
{
	//first the net has to build itself
	
	//in the input layer there will be an input for each attribute type
	net.buildInputLayer(_attrNames.size());
	//std::cout << net._inputLayer << std::endl;

	//we have the data we need from building the input layer to build the hidden layer
	net.buildHiddenLayer();
	//std::cout << net._hiddenLayer << std::endl;

	//the output layer will just have one output node
	net.buildOutputLayer();
	//std::cout << net._outputLayer << std::endl;

	std::vector<float> results;

	for(int j = 0; j < iterationNum; j++){
		for(unsigned int i = 0; i < _trainex.size(); i++){  
			setInputs(net, i);
			forwardPropogate(net);
			backPropogate_2(net, i);
			//std::cout << "gave " << _trainex[i]._values[0] << _trainex[i]._values[1] << " got " << net._outputLayer[0]._output << std::endl;
			results.push_back(net._outputLayer[0]._output);
		}
		printOutputForSingleIteration(net, j);
		std::cout << "training set: " << std::endl;
		testAccuracyOnSet(_trainex, results);
		std::cout << "testing set: " << std::endl;
		testAccuracyOnSet(_testex, results);
	}
	return 0;
}

void NetTeach::setInputs(Net& net, unsigned int iterationNum){
	for(int currentInputNeuronIndex = 0; currentInputNeuronIndex < net._inputLayer.size(); currentInputNeuronIndex++){
		net._inputLayer[currentInputNeuronIndex]._inputVal = _trainex[iterationNum]._values[currentInputNeuronIndex];
	}
}

void NetTeach::forwardPropogate(Net& net)
{
	//cycle through all the neurons in the network and calculate the output values for all of them.
	//we don't need to calculate ouputs for input neurons
	float fromInputNeuron_i;
	float sumFromInputs = 0;
	float outputForHidden_i;
	float currentInputVal;
	
	
	//calculate output for each hidden neuron
	HiddenNeuron currentHiddenNeuron;
	InputNeuron currentInputNeuron;
	Weight currentWeight;
	int currentInputNeuronIndex;
	int currentGlobalWeightIndex;
	for(int currentHiddenNeuronIndex = 0; currentHiddenNeuronIndex < net._hiddenLayer.size(); currentHiddenNeuronIndex++){

		//make a copy the current hidden neuron that we can edit
		currentHiddenNeuron = net._hiddenLayer[currentHiddenNeuronIndex];

		//now we are going to sum the input*weight from every input neuron connected to this hidden neuron
		for(int currentIncomingWeightIndex = 0; currentIncomingWeightIndex < currentHiddenNeuron._numIncomingWeights; currentIncomingWeightIndex++){

			//grab the index for the weight
			currentGlobalWeightIndex = currentHiddenNeuron._incomingWeights[currentIncomingWeightIndex];

			//grab the weight from net
			currentWeight = net._weights[currentGlobalWeightIndex];

			//grab the input neuron index connected to that weight
			currentInputNeuronIndex = net.weightController.getWeightParentNeuronIndex(currentWeight._name);

			//grab the actual input neuron
			currentInputNeuron = net._inputLayer[currentInputNeuronIndex];

			//calc the contribution as input * weight
			fromInputNeuron_i = currentInputNeuron._inputVal * currentWeight._val;

			//and add that contribution to the total sum
			sumFromInputs += fromInputNeuron_i;
		}

		//normalize that sum, and that becomes the output value
		outputForHidden_i = net.neuronController.sigmoid(sumFromInputs);
		//outputForHidden_i = sumFromInputs;

		//and record it
		net._hiddenLayer[currentHiddenNeuronIndex]._output = outputForHidden_i;
	}


	//now that we have calculated the output for each hidden node, we can take those outputs to calculate the output for the output node
	float fromHiddenNeuron_i;
	float sumFromHiddens = 0;
	float finalOutput;
	float currentHiddenNeuronOutput;
	
	for(int i = 0; i < net._hiddenLayer.size(); i++){

		//grab the output from the current hidden neuron
		currentHiddenNeuronOutput = net._hiddenLayer[i]._output;

		//grab the weight we want
		currentWeight = net.findWeight(net.weightController.genWeightName(i, 'h', 0, 'o'));

		////calc the contribution as input * weight
		fromHiddenNeuron_i = currentHiddenNeuronOutput * currentWeight._val;

		//and add that contribution to the total sum
		sumFromHiddens += fromHiddenNeuron_i;
	}
	//normalize that sum, and that becomes the output value
	finalOutput = net.neuronController.sigmoid(sumFromHiddens);

	if(finalOutput >= 0.5){
		finalOutput += .25;
	}else{
		finalOutput -= .25;
	}

	//and record it
	net._outputLayer[0]._output = finalOutput;
}

void NetTeach::forwardPropogate_2(Net& net)
{
	//cycle through all the neurons in the network and calculate the output values for all of them.
	//we don't need to calculate ouputs for input neurons
	float fromInputNeuron_i;
	float sumFromInputs = 0;
	float outputForHidden_i;
	for(int i = 0; i < net._hiddenLayer.size(); i++){
		for(int j = 0; j < net._inputLayer.size(); j++){
			//multiply the input from that neuron by the connecting weight
			fromInputNeuron_i = net._inputLayer[j]._inputVal * net.findWeight(net.weightController.genWeightName(j, 'i', i, 'h'))._val;
			sumFromInputs += fromInputNeuron_i;
		}
		outputForHidden_i = net.neuronController.sigmoid(sumFromInputs);
		net._hiddenLayer[i]._output = outputForHidden_i;
	}

	float fromHiddenNeuron_i;
	float sumFromHiddens = 0;
	float finalOutput;
	for(int i = 0; i < net._hiddenLayer.size(); i++){
		fromHiddenNeuron_i = net._hiddenLayer[i]._output * net.findWeight(net.weightController.genWeightName(i, 'h', 0, 'o'))._val;
		sumFromHiddens += fromHiddenNeuron_i;
	}
	finalOutput = net.neuronController.sigmoid(sumFromHiddens);
	net._outputLayer[0]._output = finalOutput;
}

void NetTeach::backPropogate(Net& net, unsigned int currentTrainingInstance)
{
	int classVal = _trainex[currentTrainingInstance]._class;

	//generate delta for the output node
	float errorOutputNeuron = net._outputLayer[0]._output - classVal;
	float derivOfsumOfIncoming = net.neuronController.partialDeriv(net._outputLayer[0]._sumOfIncomingtWeights);
	float deltaOutputNeuron = errorOutputNeuron * derivOfsumOfIncoming;

	float curentHiddenNeuronSumOfIncoming;
	float currentHiddenNeuronSumOfOutgoingWeights;
	float currentHiddenNeuronDeltaValue;
	float hiddenNeuronError;
	//generate delta for all hidden nodes
	for(int i =  0; i < net._hiddenLayer.size(); i++){
		//delta for hidden neurons is deriv(sum incoming weights) * sumOutgoingWeights * deltaOutputNeuron
		//curentHiddenNeuronDerivSumOfIncoming = net.neuronController.partialDeriv(net._hiddenLayer[i]._sumOfIncomingtWeights);
		curentHiddenNeuronSumOfIncoming = net._hiddenLayer[i]._sumOfIncomingtWeights;
		currentHiddenNeuronSumOfOutgoingWeights = net._weights[net._hiddenLayer[i]._outgoingWeights[0]]._val;
		//currentHiddenNeuronDeltaValue = curentHiddenNeuronDerivSumOfIncoming * (currentHiddenNeuronSumOfOutgoingWeights) * deltaOutputNeuron;
		currentHiddenNeuronDeltaValue = _learningRate * (classVal - net._outputLayer[0]._output) * curentHiddenNeuronSumOfIncoming;
		net._hiddenLayer[i]._delta = currentHiddenNeuronDeltaValue;

		hiddenNeuronError = net.neuronController.sigmoid(net._hiddenLayer[i]._output) * (errorOutputNeuron + net._weights[net._hiddenLayer[i]._outgoingWeights[0]]._val);
	}

	std::string weightname;
	//calculate all the gradients of all the weights
	for(int i = 0; i < net._weights.size(); i++){
		weightname = net._weights[i]._name;

		//if current weight connects an input node and a hidden node
		if(weightname[2] == 'i'){
			int currentInputNodeIndex = net.weightController.getWeightParentNeuronIndex(weightname);
			net._weights[i]._gradient = net._inputLayer[currentInputNodeIndex]._inputVal * deltaOutputNeuron;
		}else if(weightname[2] == 'h'){
			int currentHiddenNodeIndex = net.weightController.getWeightParentNeuronIndex(weightname);
			net._weights[i]._gradient = net._hiddenLayer[currentHiddenNodeIndex]._output * deltaOutputNeuron;
		}
	}

	//calculate all the weight updates
	for(int i = 0; i < net._weights.size(); i++){
		float newWeight = ((-1) * _learningRate * net._weights[i]._gradient) + (net._momentum * net._weights[i]._previousVal);
		net._weights[i]._previousVal = net._weights[i]._val;
		net._weights[i]._val = newWeight;
	}
}

void NetTeach::backPropogate_2(Net& net, unsigned int currentTrainingInstance){

	//calculate the error of output neuron
	int classVal = _trainex[currentTrainingInstance]._class;
	float output = net._outputLayer[0]._output;
	float sigmoidOutput = net.neuronController.sigmoid(output);
	float outputError = classVal - output;
	float errorOutputNeuron =  sigmoidOutput * outputError;

	//change output layer weights (the output neurons incoming weights)
	float currentWeight;
	OutputNeuron outputNeuron = net._outputLayer[0];
	for(int i = 0; i < outputNeuron._numIncomingWeights; i++){
		
		//grab the weight value so we can edit it
		currentWeight = net._weights[outputNeuron._incomingWeights[i]]._val;
		
		//update the weight
		currentWeight += _learningRate * errorOutputNeuron * output;

		//put the weight back
		net._weights[outputNeuron._incomingWeights[i]]._val = currentWeight;
	}

	//calculate (back propogate) hidden layer errors
	HiddenNeuron currentHiddenNeuron;
	int currentInputNeuronIndex;
	InputNeuron currentInputNeuron;
	int numHiddenNeurons = net._hiddenLayer.size();
	float currentHiddenNeuronError;
	float sigmoidCurrentHiddenNeuronOuput;
	int currentOutgoingWeightIndex;
	float currentOutgoingWeight;
	float currentGlobalWeightIndex;
	Weight currentIncomingWeight;
	
	//calculate the error and update the weight for every hidden neuron
	for(int currentHiddenNeuronIndex = 0; currentHiddenNeuronIndex < numHiddenNeurons; currentHiddenNeuronIndex++){

		//make a copy of the hidden neuron that we can edit
		currentHiddenNeuron = net._hiddenLayer[currentHiddenNeuronIndex];

		//calculate current hidden neuron error
		sigmoidCurrentHiddenNeuronOuput = net.neuronController.sigmoid(currentHiddenNeuron._output);
		currentOutgoingWeightIndex = net._hiddenLayer[currentHiddenNeuronIndex]._outgoingWeights[0];
		currentOutgoingWeight = net._weights[currentOutgoingWeightIndex]._val;
		currentHiddenNeuronError = sigmoidCurrentHiddenNeuronOuput * outputError * currentOutgoingWeight;

		//update current hidden neuron weights (the hidden neurons incoming weights) using the error we just calculated
		for(int currentIncomingWeightIndex = 0; currentIncomingWeightIndex < currentHiddenNeuron._numIncomingWeights; currentIncomingWeightIndex++){
			
			//grab the weight index from the current hidden neuron
			currentGlobalWeightIndex = currentHiddenNeuron._incomingWeights[currentIncomingWeightIndex];
			
			//grab the weight and make a copy we can edit
			currentIncomingWeight = net._weights[currentGlobalWeightIndex];
			
			//grab the index of the input neuron connected to this weight
			currentInputNeuronIndex = net.weightController.getWeightParentNeuronIndex(currentIncomingWeight._name);

			//make a copy of that neuron
			currentInputNeuron = net._inputLayer[currentInputNeuronIndex];

			//update the weight in our copy
			currentIncomingWeight._val += _learningRate * currentHiddenNeuronError * currentInputNeuron._inputVal;
			
			//copy our edited version into the global net record
			net._weights[currentGlobalWeightIndex] = currentIncomingWeight;
		}
		
	}
}

float NetTeach::testAccuracyOnSet(std::vector<Instance> examples, std::vector<float>& results)
{
	int numRight = 0;
	int numWrong = 0;
	for(int i = 0; i < examples.size(); i++){
		//std::cout << "trex: " << examples[i]._class << " res: " << (int) (results[i] + 0.5) << std::endl;
		if(examples[i]._class == (int) (results[i] + 0.5)){
			numRight++;
		}else{
			numWrong++;
		}
	}
	float accuracy = (numRight) / (float)examples.size();
	std:: cout << "accuracy: " << std::setprecision(3) << accuracy * 100 << "%" << std::endl;
	return 0;
}

void NetTeach::printOutputForSingleIteration(Net& net, unsigned int numIter){

	std::cout << "after iter "  << numIter ; 
	for(int i = 0; i < _attrNames.size(); i++){
		std::cout << "w(" << _attrNames[i] << ") = " << std::setprecision(3) << net._weights[net._inputLayer[i]._outgoingWeights[0]]._val << " ";
	}
	std::cout << "output: " << net._outputLayer[0]._output << std::endl;
}