#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <fstream>
#include <iostream>
#include "Vertex.h"
#include "Matrices.h"
#include "tree.hh"
#include "BallJoint.h"
#include "Triangle.h"

class Model{

public:

	Model(){}
	Model(tree<BallJoint> _skelTree, int _numJoints);
	//Model(const Model&);
	~Model();

	//Model& operator=(const Model& _model);
	//bool operator ==(const Model& _model) const;

	void printVerts();
	void printBindings();
	void printTransforms();
	void printTriangles();
	void drawTriangles();
	void printTree();

	void generateTransforms();
	tree<BallJoint>::iterator& Model::getJointByIndex(int _index);
	void weightVertices();

	int numJoints;

	tree<BallJoint> skelTree;
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;
	//std::vector<Matrix4> bindings;
	//std::vector<Matrix4> transforms;

};

#endif