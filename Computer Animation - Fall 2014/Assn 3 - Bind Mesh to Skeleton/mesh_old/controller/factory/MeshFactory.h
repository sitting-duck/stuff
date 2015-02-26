#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "MeshParser.h"
#include "Mesh.h"
#include "Skeleton.h"
#include "Tokenizer.h"

class MeshFactory
{

private:
	MeshParser meshParser;

	Mesh* mesh;

	Skeleton* skeleton;

	std::vector<std::string> tokens;

	Tokenizer tokenizer;

public:
	MeshFactory();

	~MeshFactory();

	std::vector<std::string> tokenizeFile(std::string& _fileName);

	Mesh* generateMeshFromFile(const char* _filename, Skeleton* _skel);

	Mesh* generateMeshFromFile(std::string& _filename, Skeleton* _skel);

	void generateTransforms();

	void weightVertices();

};
#endif
