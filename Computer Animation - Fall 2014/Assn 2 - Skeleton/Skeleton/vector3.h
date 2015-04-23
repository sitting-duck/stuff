////////////////////////////////////////
// vector3.h
////////////////////////////////////////

#ifndef CSE169_VECTOR3_H
#define CSE169_VECTOR3_H

#include "core.h"

////////////////////////////////////////////////////////////////////////////////

class Vector3 {
public:
	Vector3()											{x=0.0f; y=0.0f; z=0.0f;}
	Vector3(float x0,float y0,float z0)					{x=x0; y=y0; z=z0;}
	void Set(float x0,float y0,float z0)				{x=x0; y=y0; z=z0;}
	void Zero()											{x=y=z=0.0f;}

	// Algebra
	void Add(const Vector3 a)							{x+=a.x; y+=a.y; z+=a.z;}
	void Add(const Vector3 a,const Vector3 b)			{x=a.x+b.x; y=a.y+b.y; z=a.z+b.z;}
	void Subtract(const Vector3 a)						{x-=a.x; y-=a.y; z-=a.z;}
	void Subtract(const Vector3 a,const Vector3 b)		{x=a.x-b.x; y=a.y-b.y; z=a.z-b.z;}
	void Scale(float s)									{x*=s; y*=s; z*=s;}
	void Scale(const Vector3 a,float s)					{x=a.x*s; y=a.y*s; z=a.z*s;}

	float Dot(const Vector3 a) const					{return x*a.x+y*a.y+z*a.z;}
	void Cross(const Vector3 a,const Vector3 b)			{x=a.y*b.z-a.z*b.y; y=a.z*b.x-a.x*b.z; z=a.x*b.y-a.y*b.x;}

	void Normalize()									{float s=1.0f/sqrtf(x*x+y*y+z*z); x*=s; y*=s; z*=s;}
	void Negate()										{x=-x; y=-y; z=-z;}

	float Mag() const									{return sqrtf(x*x+y*y+z*z);}
	float Mag2() const									{return x*x+y*y+z*z;}

	float Dist2(const Vector3 a) const					{return (x-a.x)*(x-a.x)+(y-a.y)*(y-a.y)+(z-a.z)*(z-a.z);}

	void Lerp(float t,const Vector3 a,const Vector3 b)	{Scale(a,1.0f-t); x+=b.x*t; y+=b.y*t; z+=b.z*t;}

	// Misc functions
	void Print(char *name=0) const						{if(name) printf("%s=",name); printf("{%f,%f,%f}\n",x,y,z);}

	float &operator[](int i)							{return(((float*)this)[i]);}

	// Static vectors
	static Vector3 XAXIS,YAXIS,ZAXIS;
	static Vector3 ORIGIN;

public:
	float x,y,z;
};

////////////////////////////////////////////////////////////////////////////////

#endif
