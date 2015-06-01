#include "Vertex.h"

Vertex::Vertex(){
}

Vertex::Vertex(const Vertex& _vert){
	pos = _vert.pos;
	normals = _vert.normals;
	weights = _vert.weights;
}

Vertex::~Vertex(){}

Vertex& Vertex::operator=(Vertex _vert){
	pos = _vert.pos;
	normals = _vert.normals;
	weights = _vert.weights;
	return *this;
}

bool Vertex::operator==(const Vertex& _vert) const{
	if((weights == _vert.weights) && (pos == _vert.pos) && (normals == _vert.normals)){
		return true;
	}
	else{
		return false;
	}
}