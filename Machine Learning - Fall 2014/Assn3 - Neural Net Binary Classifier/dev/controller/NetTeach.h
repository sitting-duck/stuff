#ifndef NET_TEACH_H
#define NET_TEACH_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <assert.h>

#include "Instance.h"

class NetTeach
{
private:
	std::vector<std::string> _attrNames;

	std::vector<Instance> _trainex;

	std::vector<Instance> _testex;

	unsigned int _numIter;

	std::string _trainingFileName;

	std::ifstream _trainFileStream;

	std::string _testingFileName;

	std::ifstream _testFileStream;

	float _currentTrainingSetAccuracy;

	float _currentTestingSetAccuracy;


private:
	NetTeach(const NetTeach& nt);

	NetTeach& operator =(const NetTeach& nt);

public:
	NetTeach();

	NetTeach(std::string trainingFile, std::string testingFile);

	std::vector<Instance> getExamplesFromFile(std::string& filename, int exampleType);

	float teach(std::vector<Instance> trainingExamples);

	void forwardPropogate();

	void backPropogate();

	float testAccuracyOnSet(std::vector<Instance> examples);

};
#endif
