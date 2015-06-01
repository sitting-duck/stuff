#ifndef BALL_JOINT_H
#define BALL_JOINT_H

#include <string>
#include <float.h>
#include "Matrices.h"

class BallJoint{

public:
	BallJoint();
	BallJoint(const std::string& _name);
	~BallJoint();

	std::string& getName();
	void setName(const std::string& _name);
	int getDOF();

	const static int DOF = 3;
	
	bool hasBeenCalc;
	std::string name;
	double offset[DOF];
	double boxmin[DOF];
	double boxmax[DOF];
	double rotlimit[DOF][2];
	double pose[DOF];

	Matrix4 local;
	Matrix4 world;

	void calulcateLocal();
	void calculateWorld(const Matrix4& _parentWorld);

};

inline int BallJoint::getDOF(){ return DOF; }
#endif