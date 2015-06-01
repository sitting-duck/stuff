
#include <GL/glui.h>
#include "ModelFactory.h"
#include "Scene.h"

Scene scene;

//function declarations
void onDisplay();
void onReshape(int _x, int _y);
void onKeyboard(unsigned char _key, int _x, int _y);


void main(int argc, char* argv[]){
	/****************************************/
	/*   Initialize GLUT and create window  */
	/****************************************/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	scene = Scene(800, 600);

	glutCreateWindow("Bind Mesh");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(onDisplay);
	GLUI_Master.set_glutReshapeFunc(onReshape);
	GLUI_Master.set_glutKeyboardFunc(onKeyboard);

	scene.createModel("tube.skel", "tube.skin");

	glutMainLoop();
}


void onDisplay(){

	glClearColor(.9f, .9f, .9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.updateCamera();
	scene.drawMesh();
	glutWireCube(.5);
	glFlush();
	glutSwapBuffers();
}

void onReshape(int _x, int _y){

}

void onKeyboard(unsigned char _key, int _x, int _y){
	scene.keyBoardInput(_key);
}