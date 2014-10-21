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
	_name = name;
	_val = val;
}

Weight::Weight(const Weight& w)
{
	_name = w._name;
	_val = w._val;
	_previousVal = w._previousVal;
	_gradient = w._gradient;
}

Weight& Weight::operator =(const Weight& w)
{
	_name = w._name;
	_val = w._val;
	_previousVal = w._previousVal;
	_gradient = w._gradient;
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
