#ifndef SKEL_FACTORY_H
#define SKEL_FACTORY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "SkelParser.h"
#include "Skeleton.h"
#include "Tokenizer.h"

class SkelFactory
{
private:
	SkelParser skelParser;

	Skeleton* skel;

	std::vector<std::string> tokens;

	Tokenizer tokenizer;

public:
	SkelFactory();

	Skeleton* getSkeleton();

	Skeleton* generateSkelFromFile(const char* _fileName);

	Skeleton* generateSkelFromFile(std::string& _fileName);

	/** Tokenizing Functions **/
	std::vector<std::string>& tokenizeFile(std::string& _fileName);

	unsigned int getNumJoints();

	void adjustSkelForRotLimits();

	void generateLocalMatrices();

	void generateWorldMatrices();

	void generateTransformMatrices();

};
#endif
