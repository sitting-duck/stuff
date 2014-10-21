#ifndef INSTANCE_H
#define INSTANCE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "std::vector.h"
#include "const Instance.h"
#include "ostream.h"
#include "std : :ostream.h"
#include "std/vector.h"

class Instance
{
private:
	std::vector<int> _values : std:;

	unsigned int _class;

	unsigned int _numAttrs;


public:
	Instance();

	Instance(unsigned int numAttrs, std::vector<int> values, unsigned int class);

	Instance(const Instance& i);

	Instance& operator =(const Instance& i);

	ostream& operator<<(std : :ostream& os, const Instance& w);

};
#endif
