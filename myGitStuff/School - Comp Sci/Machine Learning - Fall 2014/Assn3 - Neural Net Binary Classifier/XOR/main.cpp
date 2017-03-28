
#include <vector>
#include <iostream>
#include "TrainingExample.h"
#include "TestingExample.h"
#include "XORNet.h"

using namespace std;

void main(){

	// prepare XOR traing data
	double data[][3] = {
		0, 0, 0,
		0, 1, 1,
		1, 0, 1,
		1, 1, 0 };

	vector<TrainingExample> trainingExamples;

	trainingExamples.push_back(TrainingExample(0, 0, 0));
	trainingExamples.push_back(TrainingExample(0, 1, 1));
	trainingExamples.push_back(TrainingExample(1, 0, 1));
	trainingExamples.push_back(TrainingExample(1, 1, 0));

	//prepare test data
	vector<TestingExample> testingExamples;

	testingExamples.push_back(TestingExample(0, 0));
	testingExamples.push_back(TestingExample(0, 1));
	testingExamples.push_back(TestingExample(1, 0));
	testingExamples.push_back(TestingExample(1, 1));

	XORNet xn = XORNet();
	int iter = 0;
	while(iter != 20){
		std::cout << std::endl;
		xn.forwardPropogate(trainingExamples, testingExamples);
		xn.backPropogate(trainingExamples, testingExamples);
		std::cout << std::endl;
		iter++;
	}
	std::cout << "weights" << std::endl;
	xn.printWeights();


}