#ifndef WEIGHT_H
#define WEIGHT_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "std::string.h"
#include "const Weight.h"
#include "ostream.h"
#include "std : :ostream.h"

class Weight
{
private:
	string name : std:;

	float val;

	float previousVal;

	float gradient;


public:
	Weight();

	Weight(std::string name, float val);

	Weight& Weight(const Weight& w);

	Weight& operator =(const Weight& w);

	ostream& operator<<(std : :ostream& os, const Weight& w);

};
#endif
