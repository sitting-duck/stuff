#ifndef NET_TEACH_H
#define NET_TEACH_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "string_.h"
#include "Instance.h"
#include "ifstream.h"
#include "const NetTeach.h"
#include "std::string.h"
#include "bool.h"
#include "std/vector.h"

class NetTeach
{
private:
	string_ _attrNames : vector < std:;

	std::vector<Instance> _trainex : std:;

	std::vector<Instance> _testex : std:;

	unsigned int _numIter;

	string _trainingFileName : std:;

	ifstream _trainFileStream;

	string _testingFileName : std:;

	ifstream _testFileStream;

	float _currentTrainingSetAccuracy;

	float _currentTestingSetAccuracy;


private:
	NetTeach(const NetTeach& nt);

	NetTeach& operator =(const NetTeach& nt);

public:
	NetTeach();

	NetTeach(std::string trainingFile, std::string testingFile);

	std::vector<Instance> getExamplesFromFile(std::string& filename, int exampleType);

	float teach(bool<Instance> trainingExamples);

	void forwardPropogate();

	void backPropogate();

	float testAccuracyOnSet(std::vector<Instance> examples);

};
#endif
