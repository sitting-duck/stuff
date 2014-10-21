#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Net.h"


Net::Net()
{
}

Net::Net(float learningRate, float momentum)
{
}

Net::Net(const Net& n)
{
}

Net& Net::operator =(const Net& n)
{
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Net& n)
{
	return os;
}
