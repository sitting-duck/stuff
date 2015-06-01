#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Scene.h"

Scene::Scene(){}

Scene::Scene(int width, int height){
	currJoint = 0;

	camera = Camera(width, height);
	camera.Draw();
}

Scene::~Scene(){}

Model* Scene::createModel(const char* _skelFile, const char* _meshFile){
	
	//note that the skeleton is made before the mesh.  The mesh factory will need some data from the skeleton for binding the mesh to the skel, 
	//that's why it has to be made first
	modelFactory.generateSkelFromFile(_skelFile);
	modelFactory.generateMeshFromFile(_meshFile);
	
	model = &modelFactory.model;
	return model;
}

Skeleton* Scene::createSkel(const char* _skelFile){
	modelFactory.generateSkelFromFile(_skelFile);
	model = &modelFactory.model;
	return model->skeleton;
}

void Scene::drawModel(){
	if(model->skeleton != NULL){
		drawSkel();
	}
	
	if(model->mesh != NULL){
		drawMesh();
	}
}

void Scene::draw(Mesh* _mesh)
{
	//std::cout << "draw triangles: " << std::endl;
	float x0, y0, z0, x1, y1, z1, x2, y2, z2;

	for(int i = 0; i < _mesh->triangles.size(); i++){
		x0 = _mesh->vertices[_mesh->triangles[i].vertIds[0]].position[0];
		y0 = _mesh->vertices[_mesh->triangles[i].vertIds[0]].position[1];
		z0 = _mesh->vertices[_mesh->triangles[i].vertIds[0]].position[2];

		x1 = _mesh->vertices[_mesh->triangles[i].vertIds[1]].position[0];
		y1 = _mesh->vertices[_mesh->triangles[i].vertIds[1]].position[1];
		z1 = _mesh->vertices[_mesh->triangles[i].vertIds[1]].position[2];

		x2 = _mesh->vertices[_mesh->triangles[i].vertIds[2]].position[0];
		y2 = _mesh->vertices[_mesh->triangles[i].vertIds[2]].position[1];
		z2 = _mesh->vertices[_mesh->triangles[i].vertIds[2]].position[2];

		glMatrixMode(GL_MODELVIEW);

		glBegin(GL_LINES);

		//vert 0 to vert 1
		glVertex3f(x0, y0, z0);
		glVertex3f(x1, y1, z1);

		//vert 1 to vert 2
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y2, z2);

		//vert 2 to vert 0
		glVertex3f(x2, y2, z2);
		glVertex3f(x0, y0, z0);

		glEnd();
	}
}

void Scene::drawMesh(){
	draw(model->mesh);
}

void Scene::draw(Skeleton* _skel)
{
}

void Scene::drawSkel(){
	model->skeleton->drawSkel();
}

void Scene::updateCamera(){
	camera.Draw();
}

void Scene::increaseRotateOfCurrentJoint(unsigned int _currentAxis)
{
	BallJoint* bj = &model->skeleton->operator[](currJoint);
	bj->pose[_currentAxis] += 0.2;
}

void Scene::decreaseRotateOfCurrentJoint(unsigned int _currentAxis)
{
	BallJoint* bj = &model->skeleton->operator[](currJoint);
	bj->pose[_currentAxis] -= 0.2;
}

void Scene::incrementSelectedJoint()
{
}

void Scene::decrementSelectedJoint()
{
}

void Scene::onReshape(int _x, int _y)
{
}

void Scene::drawJointBox(unsigned int _jointIndex)
{
}

void Scene::drawAxes()
{
}

void Scene::updateModel(){
	Skeleton* skel = model->skeleton;
	Mesh* mesh = model->mesh;
	if(skel != NULL){
		modelFactory.skelFactory.generateLocalMatrices();
		modelFactory.skelFactory.generateWorldMatrices();
		modelFactory.skelFactory.generateTransformMatrices();
	}
	
	if(mesh != NULL){
		modelFactory.meshFactory.weightVertices();
	}

}