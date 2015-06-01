#include "Scene.h"
#include "Window.h"
#include <windows.h>
#include <math.h>
#include <GL/glui.h>

Scene scene;
Window window;

//for identifying the main window
GLuint main_window;

//function declarations
void init();
void setupGLUI();
void onIdle(void);
void gluiCallback(int controlId);

void onDisplay();
void onReshape(int _x, int _y);
void onKeyboard(unsigned char _key, int _x, int _y);
void onMouse(int button, int state, int x, int y);
void onMotion(int x, int y);
void onEntry(int state);


//  Callback functions
void pmotion(int x, int y);
void special(int key, int x, int y);

void main(int argc, char* argv[]){
	/****************************************/
	/*   Initialize GLUT and create window  */
	/****************************************/

	glutInit(&argc, argv);

	//  Set the window x and y coordinates such that the 
	//  window becomes centered
	window.centerOnScreen();

	//  Connect to the windowing system + create a window
	//  with the specified dimensions and position
	//  + set the display mode + specify the window title.
	glutInitWindowSize(window.window_width, window.window_height);
	glutInitWindowPosition(window.window_x, window.window_y);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	main_window = glutCreateWindow("Bind Mesh");
	
	init();

	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);
	glutKeyboardFunc(onKeyboard);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	glutEntryFunc(onEntry);

	scene = Scene(800, 600);
	scene.createModel("wasp.skel", "wasp.skin");
	//scene.createSkel("tube.skel");

	window = Window(800, 600, scene);
	window.main_window = main_window;

	//  Setup all GLUI stuff
	setupGLUI();

	glutMainLoop();
}

void init(){
	//  Set the frame buffer clear color to black. 
	glClearColor(1.0, 0.0, 0.0, 0.0);
}

void setupGLUI(){
	//  Set idle function
	GLUI_Master.set_glutIdleFunc(onIdle);

	window.createOptionsWindow(gluiCallback);

	//  Let the GLUI window know where its main graphics window is
	window.glui_window->set_main_gfx_window(main_window);
}

void onDisplay(){

	glClear(GL_COLOR_BUFFER_BIT);
	scene.updateCamera();
	scene.drawModel();
	//glFlush();
	glutSwapBuffers();
}

void onReshape(int w, int h){
	//  Stay updated with the window width and height
	window.window_width = w;
	window.window_height = h;

	//  Reset viewport
	glViewport(0, 0, window.window_width, window.window_height);

	glutPostRedisplay();
}

void onKeyboard(unsigned char _key, int _x, int _y){
	window.onKeyBoardInput(_key);
}

void onIdle(void)
{
	/* According to the GLUT specification, the current window is
	undefined during an idle callback.  So we need to explicitly change
	it if necessary */
	//if(glutGetWindow() != main_window)
	glutSetWindow(main_window);
	glutPostRedisplay();
	Sleep(50);
}

void gluiCallback(int controlId){

	switch(controlId){
	case 0:
		//the item selected from the box will become the currJoint
		std::cout << "selected: " << window.listbox_item_id << std::endl;
		scene.currJoint = window.listbox_item_id;
		break;
	}
}

//-------------------------------------------------------------------------
//  This function is passed to the glutMouseFunc and is called 
//  whenever the mouse is clicked.
//-------------------------------------------------------------------------
void onMouse(int button, int state, int x, int y)
{
}

//-------------------------------------------------------------------------
//  This function is passed to the glutMotionFunc and is called 
//  whenever the mouse is dragged.
//-------------------------------------------------------------------------
void onMotion(int x, int y)
{
}

//-------------------------------------------------------------------------
//  Main Window Entry Function.
//
//	This function is called whenever the mouse pointer enters or leaves
//  the main window.
//-------------------------------------------------------------------------
void onEntry(int state)
{
}