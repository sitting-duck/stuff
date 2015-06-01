#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "JointWeight.h"
#include "Vectors.h"

class MeshParser;
class MeshFactory;
class Scene;

class Vertex
{
	friend MeshParser;
	friend MeshFactory;
	friend Scene;

private:

	//position is a vector4 only for mathematical convenience.  Positions will always only ever be 3D.
	Vector4 position;

	Vector3 normals;

	std::vector<JointWeight> weights;

public:
	Vertex();

	void checkWeights();

	void printWeights();

};
#endif
