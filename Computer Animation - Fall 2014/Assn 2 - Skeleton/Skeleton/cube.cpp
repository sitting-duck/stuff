////////////////////////////////////////
// cube.cpp
////////////////////////////////////////

#include "cube.h"

////////////////////////////////////////////////////////////////////////////////

SpinningCube::SpinningCube() {
	// Initialize constant data
	Size=1.0f;
	Position=Vector3::ORIGIN;
	Axis=Vector3::YAXIS;

	// Resets variable data
	Reset();
}

////////////////////////////////////////////////////////////////////////////////

void SpinningCube::Update() {
	// Update (animate) any variable properties
	Angle+=0.00025f;
	WorldMtx.MakeRotateUnitAxis(Axis,Angle);
	WorldMtx.d=Position;
}

////////////////////////////////////////////////////////////////////////////////

void SpinningCube::Reset() {
	// Reset dynamic variables to a default state
	Angle=0.0f;
	WorldMtx.Identity();
}

////////////////////////////////////////////////////////////////////////////////

void SpinningCube::Draw() {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(WorldMtx);
	glutWireCube(Size);
}

////////////////////////////////////////////////////////////////////////////////
