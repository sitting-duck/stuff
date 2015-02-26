#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>

using namespace std;

class Attribute{

public:

	Attribute();
	Attribute(string _name);

	string name;

	int numTrue;
	int numFalse;
	int numTrueTrue;
	int numTrueFalse;
	int numFalseFalse;
	int numFalseTrue;

};

#endif