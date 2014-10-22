#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "WeightController.h"


WeightController::WeightController()
{
}

float WeightController::calcGradient(float incoming, float outputNeuronDelta)
{
	return 0;
}

float WeightController::calcNewWeight(float learningRate, float gradient, float momentum, float prevWeight)
{
	return 0;
}

std::string WeightController::genWeightName(unsigned int firstNeuron, char firstNeuronType, unsigned int secondNeuron, char secondNeuronType){
	std::string weightname = "w_";

	std::string prefix1;
	std::string prefix2;

	char numbuf[10] = {'\0'};

	switch(firstNeuronType){
	case 'i':
		prefix1 = "i";
		break;
	case 'h':
		prefix1 = "h";
		break;
	case 'o':
		prefix1 = "o";
		break;
	default:
		std::cout << "Error: WeightController::genWeightName : invalid first neuron type" << std::endl;
	}

	switch(secondNeuronType){
	case 'i':
		prefix2 = "i";
		break;
	case 'h':
		prefix2 = "h";
		break;
	case 'o':
		prefix2 = "o";
		break;
	default:
		std::cout << "Error: WeightController::genWeightName : invalid second neuron type" << std::endl;
	}

	weightname.append(prefix1);
	itoa(firstNeuron, numbuf, 10);
	weightname.append(numbuf);
	memset(numbuf, 0, 10);

	weightname.append(prefix2);
	itoa(secondNeuron, numbuf, 10);
	weightname.append(numbuf);
	
	return weightname;
}

unsigned int WeightController::getWeightParentNeuronIndex(std::string& weightname){
	 
	weightname.erase(0, 3);
	std::string num;
	std::string charstr;

	for(int i = 0; ; i++){
		charstr = weightname[i];
		int isdigitflag = isdigit(weightname[i]);
		if( isdigitflag == 0){break;}
		num.append(charstr);
	}
	return atoi(num.c_str());
}

unsigned int WeightController::getWeightChildNeuronIndex(std::string& weightname){

	weightname.erase(0, 3);
	std::string num;
	std::string charstr;

	for(int i = 0; isdigit(weightname[i]) != true; i++){
		weightname.erase(i, 1);
	}

	weightname.erase(0, 1);

	for(int i = 0; i < weightname.size(); i++){
		charstr = weightname[i];
		num.append(charstr);
	}

	return atoi(num.c_str());
}