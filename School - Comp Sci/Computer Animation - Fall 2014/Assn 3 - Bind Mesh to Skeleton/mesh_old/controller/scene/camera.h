////////////////////////////////////////
// camera.h
////////////////////////////////////////

#ifndef CSE169_CAMERA_H
#define CSE169_CAMERA_H

#include "core.h"

////////////////////////////////////////////////////////////////////////////////

class Camera {
public:
	Camera();
	Camera(int width, int height);
	~Camera();

	void Update();
	void Reset();
	void Draw();

	// Access functions
	void SetAspect(float a)		{Aspect=a;}
	void SetDistance(float d)	{Distance=d;}
	void SetPitch(float x)		{ Pitch = x; }
	void IncPitch()				{ Pitch += 5; }
	void DecPitch()				{ Pitch -= 5; }
	void SetYaw(float y)		{ Yaw = y; }
	void IncYaw()				{ Yaw += 5; }
	void DecYaw()				{ Yaw -= 5; }
	void SetRoll(float z)		{ Roll = z; }
	void IncRoll()				{ Roll += 5; }
	void DecRoll()				{ Roll -= 5; }
	void SetIncline(float i)	{Incline=i;}

	float GetDistance()			{return Distance;}
	float GetPitch()			{ return Pitch; }
	float GetYaw()				{return Yaw;}
	float GetRoll()				{ return Roll; }
	float GetIncline()			{return Incline;}

private:
	// Perspective controls
	float FOV;		// Field of View Angle
	float Aspect;	// Aspect Ratio
	float NearClip;	// Near clipping plane distance
	float FarClip;	// Far clipping plane distance

	// Polar controls
	float Distance;	// Distance of the camera eye position to the origin
	
	float Pitch; //Rotation of the camera eye position around the X axis
	float Yaw;	// Rotation of the camera eye position around the Y axis
	float Roll; //Rotation of the camera eye position around the Z axis

	float Incline;	// Angle of the camera eye position over the XZ plane
};

////////////////////////////////////////////////////////////////////////////////

/*
The Camera class provides a simple means to controlling the 3D camera. It could
be extended to support more interactive controls. Ultimately. the camera sets the
GL projection and viewing matrices.
*/

#endif
