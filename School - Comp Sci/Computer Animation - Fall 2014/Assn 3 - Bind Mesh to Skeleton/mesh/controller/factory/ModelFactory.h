#ifndef MODEL_FACTORY_H
#define MODEL_FACTORY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "SkelFactory.h"
#include "MeshFactory.h"

class Scene;

class ModelFactory
{
	friend Scene;

private:
	SkelFactory skelFactory;

	MeshFactory meshFactory;

	Model model;

public:
	ModelFactory();

	Model* getModel();

	Skeleton* generateSkelFromFile(const char* _filename);

	Skeleton* generateSkelFromFile(std::string& _filename);

	Mesh* generateMeshFromFile(const char* _filename);

	Mesh* generateMeshFromFile(std::string& _filename);

};
#endif
