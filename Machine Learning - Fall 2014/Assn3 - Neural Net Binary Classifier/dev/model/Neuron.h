#ifndef NEURON_H
#define NEURON_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>


class Neuron
{
private:
	std::string _name;


public:
	Neuron();

	Neuron(std::string name);

	Neuron(const Neuron& n);

	Neuron& operator =(const Neuron& n);

	friend std::ostream& operator<<(std::ostream& os, const Neuron& n);

};
#endif
