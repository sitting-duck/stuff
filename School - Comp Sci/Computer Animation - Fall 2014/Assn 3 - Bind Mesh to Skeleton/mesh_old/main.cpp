

#include "Scene.h"
#include "Window.h"
#include <windows.h>
#include <math.h>
#include <GL/glui.h>

Scene scene;
Window window;

//define the window position on screen
int window_x;
int window_y;

//window size
int window_width = 600;
int window_height = 800;

GLuint main_window;
GLUI* glui_window;
int listbox_item_id = 0;

//function declarations
void init();
void setupGLUI();
void onIdle(void);
void gluiCallback(int controlId);

void onDisplay();
void onReshape(int _x, int _y);
void onKeyboard(unsigned char _key, int _x, int _y);

void centerOnScreen();

//controls are things like dropdown menus, list boxes etc.
enum controls { JOINT_LISTBOX = 0 };

void main(int argc, char* argv[]){
	/****************************************/
	/*   Initialize GLUT and create window  */
	/****************************************/

	glutInit(&argc, argv);

	//  Set the window x and y coordinates such that the 
	//  window becomes centered
	centerOnScreen();

	//  Connect to the windowing system + create a window
	//  with the specified dimensions and position
	//  + set the display mode + specify the window title.
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(window_x, window_y);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	main_window = glutCreateWindow("Bind Mesh");
	
	init();

	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);
	glutKeyboardFunc(onKeyboard);
	GLUI_Master.set_glutDisplayFunc(onDisplay);
	GLUI_Master.set_glutReshapeFunc(onReshape);
	GLUI_Master.set_glutKeyboardFunc(onKeyboard);

	scene = Scene(800, 600);
	//scene.createModel("tube.skel", "tube.skin");
	//window = Window(800, 600, scene);
	//window.main_window = main_window;

	//  Setup all GLUI stuff
	setupGLUI();

	glutMainLoop();
}

void init(){
	//  Set the frame buffer clear color to black. 
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void setupGLUI(){
	//  Set idle function
	GLUI_Master.set_glutIdleFunc(onIdle);

	//  Create GLUI window
	glui_window = GLUI_Master.create_glui("Options", 0, window_x - 235, window_y);
	

	//GLUI* glui = GLUI_Master.create_glui(" ", 0, 670, 50);
	GLUI_Listbox* joint_listbox = glui_window->add_listbox("  Select Joint  ", &listbox_item_id, JOINT_LISTBOX, gluiCallback);

	//add all the joints to joint list box
	//for(int i = 0; i < scene.model->getSkelNumJoints(); i++){
	//	joint_listbox->add_item(i, scene.model->getSkeleton()->operator[](i).getName().c_str());
	//}
	joint_listbox->add_item(1, "herp");
	joint_listbox->add_item(2, "derp");
	joint_listbox->add_item(3, "alerp");


	//select the root by default
	joint_listbox->set_int_val(0);

	//  Let the GLUI window know where its main graphics window is
	glui_window->set_main_gfx_window(main_window);
}

//-------------------------------------------------------------------------
//  This function sets the window x and y coordinates
//  such that the window becomes centered
//-------------------------------------------------------------------------
void centerOnScreen()
{
	window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
	window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
}

void onDisplay(){

	glClear(GL_COLOR_BUFFER_BIT);
	//scene.updateCamera();
	//scene.drawMesh();
	//glFlush();
	glutSwapBuffers();
}

void onReshape(int w, int h){
	//  Stay updated with the window width and height
	window_width = w;
	window_height = h;

	//  Reset viewport
	glViewport(0, 0, window_width, window_height);
}

void onKeyboard(unsigned char _key, int _x, int _y){
	scene.keyBoardInput(_key);
}

void onIdle(void)
{
	/* According to the GLUT specification, the current window is
	undefined during an idle callback.  So we need to explicitly change
	it if necessary */
	if(glutGetWindow() != main_window)
		glutSetWindow(main_window);
	glutPostRedisplay();
	Sleep(50);
}

void gluiCallback(int controlId){

	//window.onUpdateControl(controlId);

	std::cout << "A CONTROL WAS UPDATED OMG!!!" << std::endl;

	switch(controlId){
	case 0:
		//the item selected from the box will become the currJoint
		std::cout << "selected: " << listbox_item_id << std::endl;
		break;
	}

}