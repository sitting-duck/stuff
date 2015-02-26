#ifndef BALL_JOINT_H
#define BALL_JOINT_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Vectors.h"
#include "Matrices.h"
#include "Vertex.h"

class SkelParser;
class MeshParser;
class MeshFactory;
class SkelFactory;
class Scene;
class Skeleton;

class BallJoint
{
	friend SkelParser;
	friend MeshParser;
	friend MeshFactory;
	friend SkelFactory;
	friend Scene;
	friend Skeleton;

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

	std::vector<Vertex*> verticesWeightedToThisJoint;


protected:
	BallJoint();

public:
	BallJoint(int _index, std::string _name);

	void adjustPoseForRotLimits();

	void calcLocalMatrix();

	void calcLocalMatrix2();

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

	void drawBox();

	Matrix4 calcMatrixRotateAroundX(float angle);

	Matrix4 calcMatrixRotateAroundY(float angle);

	Matrix4 calcMatrixRotateAroundZ(float angle);

};
#endif
