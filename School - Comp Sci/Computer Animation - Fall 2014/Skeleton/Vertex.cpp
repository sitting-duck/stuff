#include "Vertex.h"

Vertex::Vertex(){
	for(int i = 0; i < DOF; i++){
		pos[i] = 0;
		normals[i] = 0;
	}
}

Vertex::Vertex(Vertex& _vert){
	for(int i = 0; i < DOF; i++){
		pos[i] = _vert.pos[i];
		normals[i] = _vert.normals[i];
	}
	weights = _vert.weights;
}

Vertex::~Vertex(){}

Vertex& Vertex::operator=(Vertex _vert){
	for(int i = 0; i < DOF; i++){
		pos[i] = _vert.pos[i];
		normals[i] = _vert.normals[i];
	}
	weights = _vert.weights;
	return *this;
}

bool Vertex::operator==(const Vertex& _vert) const{
	if(weights != _vert.weights){
		return false;
	}
	for(int i = 0; i < DOF; i++){
		if(pos[i] != _vert.pos[i] || normals[i] != _vert.normals[i]){
			return false;
		}
	}
	return true;
}