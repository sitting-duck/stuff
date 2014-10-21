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
	std::cout << w._name << std::endl;
	std::cout << "val: " << w._val << std::endl;
	std::cout << "previous val: " << w._previousVal << std::endl;
	std::cout << "gradient : " << w._gradient << std::endl;
	return os;
}
