
#include <string.h>
#include <GL/glui.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <conio.h>
#include <cstdlib>

void onDisplay(void);
void onReshape(int _width, int _height);
void onKeyboard(unsigned char Key, int x, int y);
void transform(float direction, int currentMode, int currentAxis);

static float xRot = 0;
static float yRot = 0;
static float zRot = 0;
static float xTran = 0;
static float yTran = 0;
static float zTran = 0;

void main(int argc, char **argv){


	//init glut and create window
	glutInit(&argc, argv);
	glutInitWindowPosition(-1, -1); //let the window manager decide where to put the window
	glutInitWindowSize(800, 800);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Transformations and Stuff");


	//regester callbacks
	glutDisplayFunc(onDisplay); 
	glutReshapeFunc(onReshape); 
	glutKeyboardFunc(onKeyboard);

	//enter GLUT processing cycle
	glutMainLoop();
}

void onDisplay(void){
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//we must set the proper mode so that we are modifying the correct matrix stack
	glMatrixMode(GL_MODELVIEW);


	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt( 0.0f, 0.0f, 2.0f,     //The camera is 2 'units' behind the center of the scene.
			   0.0f, 0.0f, 0.0f,     //the center of the scene is at the origin.  This prolly is easiest way to do things...
			   0.0f, 1.0f, 0.0f);    // specifies that Y is the UP vector, and GL figures everything else out. 
	
	//rotations
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	//translation
	glTranslatef(xTran, yTran, zTran);

	glutWireCube(.25);
	
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //reloading identity to draw 

	glutSwapBuffers();
}

//the user will first press r or t to enter rotate or translate mode
//the user will then select which axis, x,y, or z to rotate or translate on
//the user will then use the up and down arrow keys to rotate or translate.  THe up and down arrow keys designate opposite directions naturally.
void onKeyboard(unsigned char Key, int x, int y)
{
#define KB_UP 72
	#define KB_DOWN 80

	enum mode {MODE_ROTATE, MODE_TRANSLATE};
	static int currentMode = MODE_TRANSLATE;

	enum axis {X_AXIS = 1, Y_AXIS = 3, Z_AXIS = 5};
	static int currentAxis = X_AXIS;

	switch(Key)
	{
	case 27:
	case 'q':
	case 'Q':
		xRot = 0;
		yRot = 0;
		zRot = 0;
		xTran = 0;
		yTran = 0;
		zTran = 0;
		break;
	//switch to rotate mode
	case 'r':
	case 'R':
		std::cout << "rotate" << std::endl;
		currentMode = MODE_ROTATE;
		break;
	//switch to translate mode
	case 't':
	case 'T':
		std::cout << "translate" << std::endl;
		currentMode = MODE_TRANSLATE;
		break;
	//switch to x axis
	case 'x':
	case 'X':
		std::cout << "x" << std::endl;
		currentAxis = X_AXIS;
		break;
	//switch to y axis
	case 'y':
	case 'Y':
		std::cout << "y" << std::endl;
		currentAxis = Y_AXIS;
		break;
	//switch to z axis
	case 'z':
	case 'Z':
		std::cout << "z" << std::endl;
		currentAxis = Z_AXIS;
		break;
	//increase val
	case '+':
		std::cout << "up" << std::endl;
		transform(1, currentMode, currentAxis);
		break;
	//decrease val
	case '-':
		std::cout << "down" << std::endl;
		transform(-1, currentMode, currentAxis);
		break;
	};

	glutPostRedisplay();
}

void transform(float direction, int currentMode, int currentAxis){
	enum mode { MODE_ROTATE, MODE_TRANSLATE };
	enum axis { X_AXIS = 1, Y_AXIS = 3, Z_AXIS = 5 };

	int state = currentMode + currentAxis;
	std::cout << "state " << state << std::endl;

	direction *= (0.25);

	switch(state){
	//x axis + rotate mode
	case 1:
		std::cout << "rotate x " << direction << std::endl;
		xRot += direction;
		break;
	//x axis + translate mode
	case 2:
		std::cout << "translate x " << direction << std::endl;
		xTran += direction;
		break;
	//y axis + rotate mode
	case 3:
		std::cout << "rotate y " << direction << std::endl;
		yRot += direction;
		break;
	//y axis + translate mode
	case 4:
		std::cout << "translate y " << direction << std::endl;
		yTran += direction;
		break;
	//z axis + rotate
	case 5:
		std::cout << "rotate z " << direction << std::endl;
		zRot += direction;
		break;
	//z axis + translate
	case 6:
		std::cout << "translate z " << direction << std::endl;
		zTran += direction;
		break;
	default:
		std::cout << "invalid state" << std::endl;
	}
}

void onReshape(int _width, int _height){
	// Prevent a divide by zero, w_heighten window is too short
	// (you cant make a window of zero width).
	if(_height == 0)
		_height = 1;
	float ratio = 1.0* _width / _height;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, _width, _height);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}