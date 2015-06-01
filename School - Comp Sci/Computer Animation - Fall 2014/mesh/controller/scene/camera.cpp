////////////////////////////////////////
// camera.cpp
////////////////////////////////////////

#include "camera.h"

Camera::Camera(){

}
////////////////////////////////////////////////////////////////////////////////
/**
* The camera needs to be given the height and width of the window upon creation so that it can correctly set the aspect ratio
*/
Camera::Camera(int width, int height) {
	FOV = 60.0f;
	Aspect = (width/height);
	NearClip = 0.1f;
	FarClip = 100.0f;
	Distance = 5.0f;
	Pitch = 0.0f;
	Yaw = 0.0f;
	Roll = 0.0f;
	Incline = 0.0f;
}

////////////////////////////////////////////////////////////////////////////////

Camera::~Camera(){

}

void Camera::Update() {
}

////////////////////////////////////////////////////////////////////////////////

void Camera::Reset() {
	FOV=60.0f;
	Aspect=1.33f;
	NearClip=0.1f;
	FarClip=100.0f;

	Distance=5.0f;
	Pitch = 0.0f;
	Yaw=0.0f;
	Roll = 0.0f;
	Incline=0.0f;
}

////////////////////////////////////////////////////////////////////////////////

void Camera::Draw() {
	// Tell GL we are going to adjust the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set perspective projection
	gluPerspective(FOV,Aspect,NearClip,FarClip);

	// Place camera
	glTranslatef(0,0,-Distance);
	glRotatef(Incline,1.0f,0.0f,0.0f);
	glRotatef(Pitch, 1.0f, 0.0f, 0.0f);
	glRotatef(Yaw, 0.0f,1.0f,0.0f);
	glRotatef(Roll, 0.0f, 0.0f, 1.0f);

	// Return to modelview matrix mode
	glMatrixMode(GL_MODELVIEW);
}

////////////////////////////////////////////////////////////////////////////////
