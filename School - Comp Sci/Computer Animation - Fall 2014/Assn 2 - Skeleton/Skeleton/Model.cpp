#include "Model.h"

Model::Model(){}
Model::Model(const Model& _model){
	vertices = _model.vertices;
}
Model::~Model(){}

Model& Model::operator=(Model _model){
	vertices = _model.vertices;
	return *this;
}

bool Model::operator ==(const Model& _model) const{
	if(vertices == _model.vertices){
		return true;
	}
	else{
		return false;
	}
}