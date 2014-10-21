#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "NetTeach.h"


NetTeach::NetTeach()
{
}

NetTeach::NetTeach(std::string trainingFile, std::string testingFile)
{
}

std::vector<Instance> NetTeach::getExamplesFromFile(std::string& filename, int exampleType)
{
	std::vector<Instance> temp;
	return temp;
}

float NetTeach::teach(std::vector<Instance> trainingExamples)
{
	return 0;
}

void NetTeach::forwardPropogate()
{
}

void NetTeach::backPropogate()
{
}

float NetTeach::testAccuracyOnSet(std::vector<Instance> examples)
{
	return 0;
}

NetTeach::NetTeach(const NetTeach& nt)
{
}

NetTeach& NetTeach::operator =(const NetTeach& nt)
{
	return *this;
}
