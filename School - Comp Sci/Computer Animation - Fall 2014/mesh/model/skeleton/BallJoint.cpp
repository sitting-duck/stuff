#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "BallJoint.h"


BallJoint::BallJoint(int _index, std::string _name)
{
	index = _index;
	name = _name;
	parent = -1;
}

BallJoint::BallJoint()
{
}

void BallJoint::adjustPoseForRotLimits()
{
}

void BallJoint::calcLocalMatrix()
{
	//pose is a rotational value so here we are going to check the pose values against any rotational limits set in the file
	//if the pose is not greater than the max limit or less than the min limit, then we leave it alone
	for(int i = 0; i < 3; i++){
		if(pose[i] < rotLimit.getAt(i, 0)){
			pose[i] = rotLimit.getAt(i, 0);
		}
		if(pose[i] > rotLimit.getAt(i, 1)){
			pose[i] = rotLimit.getAt(i, 1);
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

void BallJoint::calcWorldMatrix(Matrix4& _parentWorld)
{
	if(index != 0)
	{
		world = _parentWorld * local;
		//world = local * _parentWorld;
	}
	else
	{
		world = local;
	}
}

void BallJoint::calcTransformMatrix()
{
	transform = world * binding.invert();
	//transform = binding.invert() * world;
}

void BallJoint::printOffsets()
{
}

void BallJoint::printBoxMins()
{
}

void BallJoint::printBoxMaxs()
{
}

void BallJoint::printPose()
{
}

void BallJoint::printRotLimits()
{
}

void BallJoint::printLocalMatrix()
{
}

void BallJoint::printWorldMatrix()
{
}

void BallJoint::printBindingMatrix()
{
}

void BallJoint::printTransformMatrix()
{
}
