#include "BallJoint.h"

BallJoint::BallJoint(){}

BallJoint::BallJoint(const std::string& _name){
	name = _name;

	for (int i = 0; i < DOF; i++){
		offset[i]   = 0.0;
		boxmin[i]   = 0.0;
		boxmax[i]   = 0.0;
		rotlimit[i][0] = 0.0;
		rotlimit[i][1] = 0.0;
		pose[i]     = 0.0;
	}
}

BallJoint::~BallJoint(){}

std::string& BallJoint::getName(){
	return name;
}
void BallJoint::setName(const std::string& _name){
	name = _name;
}