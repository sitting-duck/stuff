#include <iostream>
#include "Matrices.h"
#include "BallJoint.h"

void main(){

	Matrix4 m4;

	//construct local matrix

	//load identity matrix
	m4.identity();

	//add offset
	float offset[3] = {1, 2, 3};
	//create row
	
	float x = offset[0];
	float y = offset[1];
	float z = offset[2];

	float r1c1 = cos(y)*cos(z);
	float r1c2 = cos(y)*sin(z);
	float r1c3 = (-1)*sin(y);

	float r2c1 = (sin(x)*sin(y)*cos(z)) - (cos(x)*sin(z));
	float r2c2 = (sin(x)*sin(y)*sin(z)) + (cos(x)*cos(z));
	float r2c3 = sin(x)*cos(y);

	float r3c1 = (cos(x)*sin(y)*cos(z)) + (sin(x)*sin(z));
	float r3c2 = (cos(x)*sin(y)*sin(z)) - (sin(x)*cos(z));
	float r3c3 = cos(x)*cos(y);

	float row1[4] = {r1c1, r1c2, r1c3, 0};
	float row2[4] = {r2c1, r2c2, r2c3, 0};
	float row3[4] = {r3c1, r3c2, r3c3, 0};
	float row4[4] = {x, y, z, 1 };

	m4.setRow(1, row1);
	m4.setRow(2, row2);
	m4.setRow(3, row3);
	m4.setRow(4, row4);

}