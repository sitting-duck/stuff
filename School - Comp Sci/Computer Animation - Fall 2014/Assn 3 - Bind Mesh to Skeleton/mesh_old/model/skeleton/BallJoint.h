#ifndef BALL_JOINT_H
#define BALL_JOINT_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Vectors.h"
#include "Matrices.h"

class SkelParser;
class MeshParser;
class MeshFactory;
class SkelFactory;

class BallJoint
{
	friend SkelParser;
	friend MeshParser;
	friend MeshFactory;
	friend SkelFactory;

private:
	std::string name;

	unsigned int index;

	//not unsigned because parent is set to -1 for root
	int parent;

	Vector3 offset;

	Vector3 boxmin;

	Vector3 boxmax;

	Vector3 pose;

	Matrix3 rotLimit;

	bool rotLimitDefined;

	Matrix4 local;

	Matrix4 world;

	Matrix4 binding;

	Matrix4 transform;


protected:
	BallJoint();

public:
	BallJoint(int _index, std::string _name);

	void adjustPoseForRotLimits();

	void calcLocalMatrix();

	void calcWorldMatrix(Matrix4& _parentWorld);

	void calcTransformMatrix();

	void printOffsets();

	void printBoxMins();

	void printBoxMaxs();

	void printPose();

	void printRotLimits();

	void printLocalMatrix();

	void printWorldMatrix();

	void printBindingMatrix();

	void printTransformMatrix();

	std::string getName();

};
#endif
