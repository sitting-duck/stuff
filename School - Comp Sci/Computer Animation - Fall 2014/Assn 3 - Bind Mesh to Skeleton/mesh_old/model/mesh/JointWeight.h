#ifndef JOINT_WEIGHT_H
#define JOINT_WEIGHT_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

class MeshParser;
class MeshFactory;

class JointWeight
{
	friend MeshParser;
	friend MeshFactory;

private:
	unsigned int index;

	float weight;

public:
	JointWeight();

	JointWeight(int _jointIndex, float _weight);

	void setWeight(float _weight);

	float getWeight();

	void printJointWeight();

};
#endif
