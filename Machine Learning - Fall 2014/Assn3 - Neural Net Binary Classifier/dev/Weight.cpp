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

Weight& Weight::Weight(const Weight& w)
{
	return 0;
}

Weight& Weight::operator =(const Weight& w)
{
	return 0;
}

ostream& Weight::operator<<(std : :ostream& os, const Weight& w)
{
	return 0;
}
