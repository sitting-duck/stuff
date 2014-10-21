#ifndef WEIGHT_H
#define WEIGHT_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

class InputNeuron;
class OutputNeuron;
class HiddenNeuron;
class Net;

class Weight
{	
	friend InputNeuron;
	friend OutputNeuron;
	friend HiddenNeuron;
	friend Net;

private:
	std::string _name;

	float _val;

	float _previousVal;

	float _gradient;

public:
	Weight();

	Weight(std::string name, float val);

	Weight(const Weight& w);

	Weight& operator =(const Weight& w);

	friend std::ostream& operator<<(std::ostream& os, const Weight& w);

	friend std::ostream& operator<<(std::ostream& os, const InputNeuron& in);

	friend std::ostream& operator<<(std::ostream& os, const HiddenNeuron& hn);

	friend std::ostream& operator << (std::ostream& os, const OutputNeuron& on);

	friend std::ostream& operator << (std::ostream& os, std::vector<InputNeuron>& inv);
};
#endif
