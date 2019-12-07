#ifndef NET_TEACH_H
#define NET_TEACH_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <iomanip>

#include "Instance.h"
#include "Net.h"

class NetTeach
{
private:
	enum exampleType {TRAINING, TESTING};

	std::vector<std::string> _attrNames;

	std::vector<Instance> _trainex;

	std::vector<Instance> _testex;

	unsigned int _numTotalIter;

	float _learningRate;

	float _currentTrainingSetAccuracy;

	float _currentTestingSetAccuracy;

public:
	NetTeach();

	NetTeach(float learningRate, unsigned int numIter);

	NetTeach(const NetTeach& nt);

	NetTeach& operator =(const NetTeach& nt);

	std::vector<Instance> getExamplesFromFile(std::string& filename);

	void setTrainingExamples(std::vector<Instance> trainex);

	void setTestingExamples(std::vector<Instance> testex);

	float teach(Net& net, unsigned int iterationNum);

	void setInputs(Net& net, unsigned int iterationNum);

	void forwardPropogate(Net& net);

	void forwardPropogate_2(Net& net);

	void backPropogate(Net& net, unsigned int currentTrainingInstance);

	void backPropogate_2(Net& net, unsigned int currentTrainingInstance);

	float testAccuracyOnSet(std::vector<Instance> examples, std::vector<float>& results);

	void printOutputForSingleIteration(Net& net, unsigned int numIter);

};
#endif
