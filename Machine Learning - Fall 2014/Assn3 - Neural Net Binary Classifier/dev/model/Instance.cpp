#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Instance.h"


Instance::Instance()
{
}

Instance::Instance(unsigned int numAttrs, std::vector<int> values, unsigned int classVal)
{
}

Instance::Instance(const Instance& i)
{
}

Instance& Instance::operator =(const Instance& i)
{
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Instance& w)
{
	return os;
}
