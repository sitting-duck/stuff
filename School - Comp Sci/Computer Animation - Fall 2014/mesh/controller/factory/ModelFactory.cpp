#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ModelFactory.h"

ModelFactory::ModelFactory()
{
}

Model* ModelFactory::getModel()
{
	return &model;
}

Skeleton* ModelFactory::generateSkelFromFile(const char* _filename){
	std::string str(_filename);
	return generateSkelFromFile(str);
}

Skeleton* ModelFactory::generateSkelFromFile(std::string& _filename)
{
	model.skeleton = skelFactory.generateSkelFromFile(_filename);
	return model.skeleton;
}

Mesh* ModelFactory::generateMeshFromFile(const char* _filename){
	std::string str(_filename);
	return generateMeshFromFile(str);
}

Mesh* ModelFactory::generateMeshFromFile(std::string& _filename)
{
	model.mesh = meshFactory.generateMeshFromFile(_filename, model.skeleton);
	return model.mesh;
}
