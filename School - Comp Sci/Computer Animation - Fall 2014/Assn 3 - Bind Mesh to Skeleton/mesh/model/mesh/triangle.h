#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Vectors.h"

class MeshParser;
class Scene;

class Triangle
{
	friend MeshParser;
	friend Scene;

private:
	Vector3 vertIds;

public:
	Triangle();

	void printTriangle();

};
#endif
