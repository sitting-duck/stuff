#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Skeleton.h"
#include "Mesh.h"

class Scene;
class ModelFactory;

class Model
{
	friend ModelFactory;
	friend Scene;

private:
	Skeleton* skeleton;

	Mesh* mesh;

public:
	Model();

	//Model(const char* skelFile, const char* meshFile);

	//Model(std::string& skelFile, std::string& meshFile);

	Skeleton* getSkeleton();

	Mesh* getMesh();

};
#endif
