
#include <iostream>
#include "camera.h"

void myGlutDisplay();
void myGlutReshape(int x, int y);
void myGlutKeyboard(unsigned char Key, int x, int y);

Camera camera;

void main(int argc, char* argv[]){

	camera = Camera();
	camera.SetAspect(600 / 600);

	/****************************************/
	/*   Initialize GLUT and create window  */
	/****************************************/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 600);

	glutCreateWindow("Assn 1");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(myGlutDisplay);
	glutReshapeFunc(myGlutReshape);
	glutKeyboardFunc(myGlutKeyboard);

	glutMainLoop();
}

void myGlutDisplay(){

	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutWireCube(1);
	//camera.IncYaw();
	//camera.SetYaw(45);
	//camera.SetPitch(45);
	camera.Draw();
	
	glFlush();
	glutSwapBuffers();

}

void myGlutReshape(int x, int y){}

void myGlutKeyboard(unsigned char Key, int x, int y){

	enum TransformMode{CAMERA_MODE, JOINT_MODE};

	enum CameraTransforms{CAMERA_ROTATE, CAMERA_TRANSFORM};

	//No need for JointTransforms enum because joints should only rotate

	enum Axis {AXIS_X, AXIS_Y, AXIS_Z};

	//set defaults
	static int currentAxis = AXIS_Y;
	static int currentTransformMode = CAMERA_MODE;
	static int currentCameraTransformsMode = CAMERA_ROTATE;

	switch(Key){

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
			std::cout << "inc pitch" << std::endl;
			
		}
		else if(currentTransformMode == CAMERA_MODE && currentAxis == AXIS_Y){
			camera.IncYaw();
			std::cout << "inc yaw" << std::endl;
		}
		else if(currentTransformMode == CAMERA_MODE && currentAxis == AXIS_Z){
			camera.IncRoll();
			std::cout << "inc roll" << std::endl;
		}
		break;
	case '-':
		if(currentTransformMode == CAMERA_MODE && currentAxis == AXIS_X){
			camera.DecPitch();
			std::cout << "dec pitch" << std::endl;

		}
		else if(currentTransformMode == CAMERA_MODE && currentAxis == AXIS_Y){
			camera.DecYaw();
			std::cout << "dec yaw" << std::endl;
		}
		else if(currentTransformMode == CAMERA_MODE && currentAxis == AXIS_Z){
			camera.DecRoll();
			std::cout << "dec roll" << std::endl;
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

	glutPostRedisplay();

}