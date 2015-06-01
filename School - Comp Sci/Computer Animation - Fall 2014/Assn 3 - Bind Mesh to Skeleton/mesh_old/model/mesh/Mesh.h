#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Vertex.h"
#include "Triangle.h"

class MeshParser;
class MeshFactory;
class Scene;

class Mesh
{
	friend MeshParser;
	friend MeshFactory;
	friend Scene;

private:
	std::vector<Vertex> vertices;

	std::vector<Triangle> triangles;

public:
	Mesh();

	Mesh(std::vector<Vertex> _vertices, std::vector<Triangle> _triangles);

	void printVerts();

	void printTriangles();

};
#endif
