#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Weight.h"


Weight::Weight()
{
}

Weight::Weight(std::string name, float val)
{
}

Weight::Weight(const Weight& w)
{
}

Weight& Weight::operator =(const Weight& w)
{
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Weight& w)
{
	return os;
}
