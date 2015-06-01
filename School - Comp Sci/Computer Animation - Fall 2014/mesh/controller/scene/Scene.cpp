#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Scene.h"

Scene::Scene(){}

Scene::Scene(int width, int height){
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

void Scene::updateCamera(){
	camera.Draw();
}

void Scene::onKeyBoard(unsigned char _key)
{
}

void Scene::increaseRotateOfCurrentJoint(unsigned int _currentAxis)
{
}

void Scene::decreaseRotateOfCurrentJoint(unsigned int _currentAxis)
{
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

void Scene::keyBoardInput(unsigned char _key)
{
	enum TransformMode{ CAMERA_MODE, JOINT_MODE };

	enum CameraTransforms{ CAMERA_ROTATE, CAMERA_TRANSFORM };

	//No need for JointTransforms enum because joints should only rotate

	enum Axis { AXIS_X, AXIS_Y, AXIS_Z };

	//set defaults
	static int currentAxis = AXIS_Y;
	static int currentTransformMode = CAMERA_MODE;
	static int currentCameraTransformsMode = CAMERA_ROTATE;

	switch(_key){

	case 'c':
		currentTransformMode = CAMERA_MODE;
		std::cout << "camera mode" << std::endl;
		break;
	case 'j':
		currentTransformMode = JOINT_MODE;
		std::cout << "joint mode" << std::endl;
		break;
	case 'x':
		currentAxis = AXIS_X;
		std::cout << "axis = x" << std::endl;
		break;
	case 'y':
		currentAxis = AXIS_Y;
		std::cout << "axis = y" << std::endl;
		break;
	case 'z':
		currentAxis = AXIS_Z;
		std::cout << "axis = z" << std::endl;
		break;
	case 't':
		if(currentTransformMode == CAMERA_MODE){
			currentCameraTransformsMode = CAMERA_TRANSFORM;
			std::cout << "camera transform mode" << std::endl;
		}
		else if(currentTransformMode == JOINT_MODE){
			std::cout << "Error: cannot transform joints. Can only rotate joints, scene mode remains unchanged." << std::endl;
		}
		break;

	case 'r':
		if(currentTransformMode == CAMERA_MODE){
			currentCameraTransformsMode = CAMERA_ROTATE;
			std::cout << "camera rotate mode" << std::endl;
		}
		break;
	case '+':
		if(currentTransformMode == CAMERA_MODE && currentAxis == AXIS_X){
			camera.IncPitch();
			//std::cout << "inc pitch" << std::endl;

		}
		else if(currentTransformMode == CAMERA_MODE && currentAxis == AXIS_Y){
			camera.IncYaw();
			//std::cout << "inc yaw" << std::endl;
		}
		else if(currentTransformMode == CAMERA_MODE && currentAxis == AXIS_Z){
			camera.IncRoll();
			//std::cout << "inc roll" << std::endl;
		}
		break;
	case '-':
		if(currentTransformMode == CAMERA_MODE && currentAxis == AXIS_X){
			camera.DecPitch();
			//std::cout << "dec pitch" << std::endl;

		}
		else if(currentTransformMode == CAMERA_MODE && currentAxis == AXIS_Y){
			camera.DecYaw();
			//std::cout << "dec yaw" << std::endl;
		}
		else if(currentTransformMode == CAMERA_MODE && currentAxis == AXIS_Z){
			camera.DecRoll();
			//std::cout << "dec roll" << std::endl;
		}
		break;
	case '<':
		std::cout << "decrement joint" << std::endl;
		//decrement joint
		break;
	case '>':
		//increment joint
		std::cout << "increment joint" << std::endl;
		break;
	case '\b':
		exit(0);
	}

	camera.Draw();
	glutPostRedisplay();
}
