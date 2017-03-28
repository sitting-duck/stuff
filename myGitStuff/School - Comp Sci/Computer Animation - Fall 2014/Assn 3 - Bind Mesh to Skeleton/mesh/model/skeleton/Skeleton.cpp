#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "GL/glui.h"
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

int Skeleton::getNumJoints(){
	return skel.size();
}

void Skeleton::drawSkel(){
	for(BallJoint joint : skel){
		glPushMatrix();
		glLoadIdentity();
		glLoadMatrixf(joint.world.get());
		
		joint.drawBox();

		glPopMatrix();
	}
}

void Skeleton::setBoxesToDefault(){
	for(auto& joint : skel){
		joint.boxmin[0] = -.1;
		joint.boxmin[1] = -.1;
		joint.boxmin[2] = -.1;

		joint.boxmax[0] = .1;
		joint.boxmax[1] = .1;
		joint.boxmax[2] = .1;
	}
}