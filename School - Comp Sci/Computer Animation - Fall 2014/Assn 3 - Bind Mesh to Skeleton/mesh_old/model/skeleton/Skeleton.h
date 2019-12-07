#ifndef SKELETON_H
#define SKELETON_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "BallJoint.h"

class SkelFactory;
class MeshFactory;
class SkelParser;
class MeshParser;
class BallJoint;

class Skeleton
{
	friend SkelFactory;
	friend MeshFactory;
	friend SkelParser;
	friend MeshParser;
	friend BallJoint;

private:
	std::vector<BallJoint> skel;

public:
	Skeleton();

	BallJoint& operator[](unsigned int _index);

	BallJoint operator[](unsigned int _index) const;

	void push(BallJoint _bj);

	void rotateJoint(unsigned int _index, unsigned int _axis, float _angle);

	int getNumJoints();

};
#endif
