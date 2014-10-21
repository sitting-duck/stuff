#ifndef WEIGHT_H
#define WEIGHT_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

class Weight
{
private:
	std::string name;

	float val;

	float previousVal;

	float gradient;


public:
	Weight();

	Weight(std::string name, float val);

	Weight(const Weight& w);

	Weight& operator =(const Weight& w);

	friend std::ostream& operator<<(std::ostream& os, const Weight& w);

};
#endif
