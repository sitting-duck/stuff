#include "Triangle.h"

Triangle::Triangle(){

}

Triangle::Triangle(const Triangle& _tri){
	verts[0] = _tri.verts[0];
	verts[1] = _tri.verts[1];
	verts[2] = _tri.verts[2];
}

Triangle::~Triangle(){

}

bool Triangle::operator==(const Triangle& _tri) const{
	return ((verts[0] == _tri.verts[0]) 
		 && (verts[1] == _tri.verts[1]) 
		 && (verts[2] == _tri.verts[2])) 
		 ? true : false;
}

Triangle& Triangle::operator=(const Triangle& _tri){
	verts[0] = _tri.verts[0];
	verts[1] = _tri.verts[1];
	verts[2] = _tri.verts[2];
	return *this;
}