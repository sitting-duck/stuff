#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Camera.h"
#include "ModelFactory.h"

class Scene
{
public:
	Model* model;

	Camera camera;

	ModelFactory modelFactory;

	int currJoint;

public:

	Scene();

	Scene(int width, int height);

	~Scene();

	Model* createModel(const char* _skelFile, const char* _meshFile);

	void draw(Mesh* _mesh);

	void drawMesh();

	void draw(Skeleton* _skel);

	void updateCamera();

	void onKeyBoard(unsigned char _key);

	void increaseRotateOfCurrentJoint(unsigned int _currentAxis);

	void decreaseRotateOfCurrentJoint(unsigned int _currentAxis);

	void incrementSelectedJoint();

	void decrementSelectedJoint();

	void onReshape(int _x, int _y);

	void drawJointBox(unsigned int _jointIndex);

	void drawAxes();

	void keyBoardInput(unsigned char _key);

};
#endif
