#ifndef BALL_JOINT_H
#define BALL_JOINT_H

#include <string>

class BallJoint{

public:
	BallJoint();
	BallJoint(const std::string& _name);
	~BallJoint();

	std::string& getName();
	void setName(const std::string& _name);
	int getDOF();

	const static int DOF = 3;
	
	std::string name;
	double offset[DOF];
	double boxmin[DOF];
	double boxmax[DOF];
	double rotlimit[DOF][2];
	double pose[DOF];

};

inline int BallJoint::getDOF(){ return DOF; }
#endif