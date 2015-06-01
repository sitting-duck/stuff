#include "BallJoint.h"

BallJoint::BallJoint(){}

BallJoint::BallJoint(const std::string& _name){
	index = -1;
	hasBeenCalc = false;
	name = _name;

	for (int i = 0; i < DOF; i++){
		offset[i]   = 0.0;
		boxmin[i]   = 0.0;
		boxmax[i]   = 0.0;
		rotlimit[i][0] = DBL_MIN;
		rotlimit[i][1] = DBL_MAX;
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

void BallJoint::calulcateLocal(){

	//pose is a rotational value so here we are going to check the pose values against any rotational limits set in the file
	//if the pose is not greater than the max limit or less than the min limit, then we leave it alone
	for(int i = 0; i < DOF; i++){
		if(pose[i] < rotlimit[i][0]){
			pose[i] = rotlimit[i][0];
		}
		else if(pose[i] > rotlimit[i][1]){
			pose[i] = rotlimit[i][1];
		}
	}

	float px = pose[0];
	float py = pose[1];
	float pz = pose[2];

	float r1c1 = cos(py)*cos(pz);
	float r1c2 = cos(py)*sin(pz);
	float r1c3 = (-1)*sin(py);

	float r2c1 = (sin(px)*sin(py)*cos(pz)) - (cos(px)*sin(pz));
	float r2c2 = (sin(px)*sin(py)*sin(pz)) + (cos(px)*cos(pz));
	float r2c3 = sin(px)*cos(py);

	float r3c1 = (cos(px)*sin(py)*cos(pz)) + (sin(px)*sin(pz));
	float r3c2 = (cos(px)*sin(py)*sin(pz)) - (sin(px)*cos(pz));
	float r3c3 = cos(px)*cos(py);

	float row1[4] = { r1c1, r1c2, r1c3, offset[0] };
	float row2[4] = { r2c1, r2c2, r2c3, offset[1] };
	float row3[4] = { r3c1, r3c2, r3c3, offset[2] };
	float row4[4] = { 0, 0, 0, 1 };

	//float row1[4] = { r1c1, r1c2, r1c3,  0};
	//float row2[4] = { r2c1, r2c2, r2c3,  0};
	//float row3[4] = { r3c1, r3c2, r3c3,  0};
	//float row4[4] = { offset[0], offset[1], offset[2], 1 };

	local.setRow(0, row1);
	local.setRow(1, row2);
	local.setRow(2, row3);
	local.setRow(3, row4);
}

void BallJoint::calculateWorld(const Matrix4& _parentWorld){
	//world = local*_parentWorld;
	world = _parentWorld*local;
}