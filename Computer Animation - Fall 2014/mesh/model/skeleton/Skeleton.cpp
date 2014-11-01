#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Skeleton.h"

Skeleton::Skeleton()
{
}

//note: this function assumes that the balljoint at said index exists. Otherwise, there will be a runtime error.
BallJoint& Skeleton::operator[](unsigned int _index)
{
	return skel[_index];
}

BallJoint Skeleton::operator[](unsigned int _index) const
{
	return skel[_index];
}

void Skeleton::push(BallJoint _bj){
	skel.push_back(_bj);
}

void Skeleton::rotateJoint(unsigned int _index, unsigned int _axis, float _angle)
{
}
