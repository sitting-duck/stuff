#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Model.h"

Model::Model()
{
}

//Model::Model(const char* skelFile, const char* meshFile){
//	std::string skelFileStrObject(skelFile);
//	std::string meshFileStrObject(meshFile);
//	Model(skelFileStrObject, meshFileStrObject);
//}

//Model::Model(std::string& skelFile, std::string& meshFile){
//	
//}

Skeleton* Model::getSkeleton()
{
	return skeleton;
}

Mesh* Model::getMesh()
{
	return mesh;
}
