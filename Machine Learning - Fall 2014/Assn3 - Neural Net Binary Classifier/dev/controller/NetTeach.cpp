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
	_numIter = numIter;
}

NetTeach::NetTeach(const NetTeach& nt)
{
	_learningRate = nt._learningRate;
	_numIter = nt._numIter;
}

NetTeach& NetTeach::operator =(const NetTeach& nt)
{
	_learningRate = nt._learningRate;
	_numIter = nt._numIter;
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

float NetTeach::teach(Net& net)
{
	//first the net has to build itself
	
	//in the input layer there will be an input for each attribute type
	net.buildInputLayer(_attrNames.size());

	forwardPropogate(net);
	backPropogate(net);
	testAccuracyOnSet(_trainex);
	return 0;
}

void NetTeach::forwardPropogate(Net& net)
{
	//cycle through all the neurons in the network and calculate the output values for all of them.

}

void NetTeach::backPropogate(Net& net)
{
}

float NetTeach::testAccuracyOnSet(std::vector<Instance> examples)
{
	return 0;
}
