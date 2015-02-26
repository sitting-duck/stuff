//*************************************************************************
//
//  File Name	: GLUI Window Template
//  Author		: Ali BaderEddin
//  Created		: December 2003
//  Modified	: July 2007
//  
//  Description	: Openning an OpenGL GLUT window along with a GLUI window
//				  containing controls to manipulate objects in the OpenGL
//				  graphics context.
//  
//*************************************************************************

//  Include windows library in order to use the Sleep function
#include <windows.h>

//  For sqrt
#include <math.h>

//  Include GLUI, GLUT, OpenGL, and GLU libraries
#include <gl/glui.h>

//*************************************************************************
//  GLUT Declarations
//*************************************************************************

//  Initialization
void init();

//  Callback functions
void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void pmotion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void entry(int state);

//  define the window position on screen
int window_x;
int window_y;

//  variables representing the window size
int window_width = 512;
int window_height = 512;

//  variable representing the window title
char *window_title = "GLUI Window Template";

//  The id of the main window
GLuint main_window;

//  Tells whether to display the window full screen or not
//  Press Alt + Esc to exit a full screen.
int full_screen = 0;

//*************************************************************************
//  GLUI Declarations
//*************************************************************************

//  pointer to the GLUI window
GLUI * glui_window;

//  Declare live variables (related to GLUI)
int wireframe = 1;			//  Related to Wireframe Check Box
int draw = 1;				//  Related to Draw Check Box
int listbox_item_id = 12;	//  Id of the selected item in the list box
int radiogroup_item_id = 0; //  Id of the selcted radio button
float rotation_matrix[16]	//  Rotation Matrix Live Variable Array
= { 1.0, 0.0, 0.0, 0.0,
0.0, 1.0, 0.0, 0.0,
0.0, 0.0, 1.0, 0.0,
0.0, 0.0, 0.0, 1.0 };
float translate_xy[2]		//  Translation XY Live Variable
= { 0, 0 };
float translate_z = 0;		//  Translation Z Live Variable
float scale = 1;			//  Spinner Scale Live Variable

// an array of RGB components
float color[] = { 1.0, 1.0, 1.0 };

//  Set up the GLUI window and its components
void setupGLUI();

//  Idle callack function
void idle();

//  Declare callbacks related to GLUI
void glui_callback(int arg);

//  Declare the IDs of controls generating callbacks
enum
{
	COLOR_LISTBOX = 0,
	OBJECTYPE_RADIOGROUP,
	TRANSLATION_XY,
	TRANSLATION_Z,
	ROTATION,
	SCALE_SPINNER,
	QUIT_BUTTON
};

//  The different GLUT shapes
enum GLUT_SHAPES
{
	GLUT_WIRE_CUBE = 0,
	GLUT_SOLID_CUBE,
	GLUT_WIRE_SPHERE,
	GLUT_SOLID_SPHERE,
	GLUT_WIRE_CONE,
	GLUT_SOLID_CONE,
	GLUT_WIRE_TORUS,
	GLUT_SOLID_TORUS,
	GLUT_WIRE_DODECAHEDRON,
	GLUT_SOLID_DODECAHEDRON,
	GLUT_WIRE_OCTAHEDRON,
	GLUT_SOLID_OCTAHEDRON,
	GLUT_WIRE_TETRAHEDRON,
	GLUT_SOLID_TETRAHEDRON,
	GLUT_WIRE_ICOSAHEDRON,
	GLUT_SOLID_ICOSAHEDRON,
	GLUT_WIRE_TEAPOT,
	GLUT_SOLID_TEAPOT
};

//  Support Functions
void centerOnScreen();
void drawObject();
void printMatrixf(float *matrix);

//*************************************************************************
//  GLUT Functions.
//*************************************************************************

//-------------------------------------------------------------------------
//  Set OpenGL program initial state.
//-------------------------------------------------------------------------
void init()
{
	//  Set the frame buffer clear color to black. 
	glClearColor(0.0, 0.0, 0.0, 0.0);
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

//-------------------------------------------------------------------------
//  Function to print matrix on command prompt.
//-------------------------------------------------------------------------
void printMatrixf(float *matrix)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			printf("%f%\t", matrix[i * 4 + j]);
		}

		printf("\n");
	}
}

//-------------------------------------------------------------------------
//  This function is passed to glutDisplayFunc in order to display 
//	OpenGL contents on the window.
//-------------------------------------------------------------------------
void display(void)
{
	//  Notify that this is a GLUT Callback
	//printf ("GLUT: ");

	//  Show when are displaying an object
	//printf ("Displaying object...\n");

	//  Clear the window 
	glClear(GL_COLOR_BUFFER_BIT);

	//  Set the color
	glColor3fv(color);


	//  Swap contents of backward and forward frame buffers
	glutSwapBuffers();
}

//-------------------------------------------------------------------------
//  This function is passed to the glutReshapeFunc and is called 
//  whenever the window is resized.
//-------------------------------------------------------------------------
void reshape(int w, int h)
{
	//  Notify that this is a GLUT Callback
	printf("GLUT: ");

	//  Stay updated with the window width and height
	window_width = w;
	window_height = h;

	//  Reset viewport
	glViewport(0, 0, window_width, window_height);

	//  Print current width and height on the screen
	printf("Window Width: %d, Window Height: %d.\n", window_width, window_height);
}

//*************************************************************************
//  GLUI Functions.
//*************************************************************************
void myGlutKeyboard(unsigned char key, int x, int y) {

}
void myGlutMouse(int button, int state, int x, int y) {

}


//-------------------------------------------------------------------------
//  Setup GLUI stuff.
//-------------------------------------------------------------------------
void setupGLUI()
{
	//  Set idle function
	GLUI_Master.set_glutIdleFunc(idle);
	GLUI_Master.set_glutReshapeFunc(reshape);
	GLUI_Master.set_glutKeyboardFunc(myGlutKeyboard);
	GLUI_Master.set_glutMouseFunc(myGlutMouse);

	//  Create GLUI window
	glui_window = GLUI_Master.create_glui("Options", 0, window_x - 235, window_y);
	//glui_window = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_LEFT);

	//---------------------------------------------------------------------
	// 'Object Properties' Panel
	//---------------------------------------------------------------------

	//  Add the 'Object Properties' Panel to the GLUI window
	GLUI_Panel *op_panel = glui_window->add_panel("Object Properties");


	//  Add the Color listbox to the 'Object Properties' Panel
	GLUI_Listbox *color_listbox = glui_window->add_listbox_to_panel(op_panel,
		"Color", &listbox_item_id, COLOR_LISTBOX, glui_callback);

	//  Add the items to the listbox
	color_listbox->add_item(1, "Black");
	color_listbox->add_item(2, "Blue");
	color_listbox->add_item(3, "Cyan");
	//color_listbox->add_item(4, "Dark Grey");
	//color_listbox->add_item(5, "Grey");
	//color_listbox->add_item(6, "Green");
	//color_listbox->add_item(7, "Light Grey");
	//color_listbox->add_item(8, "Magenta");
	//color_listbox->add_item(9, "Orange");
	//color_listbox->add_item(10, "Pink");
	//color_listbox->add_item(11, "Red");
	//color_listbox->add_item(12, "White");
	//color_listbox->add_item(13, "Yellow");

	//  Select the White Color by default
	color_listbox->set_int_val(12);

	//---------------------------------------------------------------------
	// 'Transformation' Panel
	//---------------------------------------------------------------------
	for(int i = 0; i < 5; i++){
		//glui_window->add_separator();
		glui_window->add_statictext("");
	}
	
	//GLUI_Panel *transformation_panel = glui_window->add_panel("Transformation");	
	//GLUI_Panel *transformation_panel1 = glui_window->add_panel_to_panel(transformation_panel, "");
	//GLUI_Translation *translation_xy = glui_window->add_translation_to_panel(transformation_panel1, "Translation XY", GLUI_TRANSLATION_XY, translate_xy, TRANSLATION_XY, glui_callback);
	//translation_xy->set_speed(0.005);
	//glui_window->add_column_to_panel(transformation_panel1, false);
	//GLUI_Translation *translation_z = glui_window->add_translation_to_panel(transformation_panel1, "Translation Z", GLUI_TRANSLATION_Z, &translate_z, TRANSLATION_Z, glui_callback);
	//translation_z->set_speed(0.005);
	//GLUI_Panel *transformation_panel2 = glui_window->add_panel_to_panel(transformation_panel, "");
	//glui_window->add_rotation_to_panel(transformation_panel2, "Rotation", rotation_matrix, ROTATION, glui_callback);
	//glui_window->add_separator_to_panel(transformation_panel2);
	//GLUI_Spinner *spinner = glui_window->add_spinner_to_panel(transformation_panel2, "Scale", GLUI_SPINNER_FLOAT, &scale, SCALE_SPINNER, glui_callback);
	//spinner->set_float_limits(-4.0, 4.0);

	//---------------------------------------------------------------------
	// 'Quit' Button
	//---------------------------------------------------------------------

	//  Add the Quit Button
	//glui_window->add_button("Quit", QUIT_BUTTON, glui_callback);

	//  Let the GLUI window know where its main graphics window is
	//glui_window->set_main_gfx_window(main_window);
}

//-------------------------------------------------------------------------
//  GLUI callback function.
//-------------------------------------------------------------------------
void glui_callback(int control_id)
{
	//  Notify that this is a GLUI Callback
	printf("GLUI: ");

	//  Behave based on control ID
	switch (control_id)
	{
		//  Color Listbox item changed
	case COLOR_LISTBOX:

		printf("Color List box item changed: ");
		printf("listbox item %d was clicked\n", listbox_item_id);
		/*
		switch(listbox_item_id)
		{
			//  Select black color
		case 1:
			color[0] = 0 / 255.0;
			color[1] = 0 / 255.0;
			color[2] = 0 / 255.0;
			break;
			//  Select blue color
		case 2:
			color[0] = 0 / 255.0;
			color[1] = 0 / 255.0;
			color[2] = 255 / 255.0;
			break;
			//  Select cyan color
		case 3:
			color[0] = 0 / 255.0;
			color[1] = 255 / 255.0;
			color[2] = 255 / 255.0;
			break;
			//  Select dark grey color
		case 4:
			color[0] = 64 / 255.0;
			color[1] = 64 / 255.0;
			color[2] = 64 / 255.0;
			break;
			//  Select grey color
		case 5:
			color[0] = 128 / 255.0;
			color[1] = 128 / 255.0;
			color[2] = 128 / 255.0;
			break;
			//  Select green color
		case 6:
			color[0] = 0 / 255.0;
			color[1] = 255 / 255.0;
			color[2] = 0 / 255.0;
			break;
			//  Select light gray color
		case 7:
			color[0] = 192 / 255.0;
			color[1] = 192 / 255.0;
			color[2] = 192 / 255.0;
			break;
			//  Select magenta color
		case 8:
			color[0] = 192 / 255.0;
			color[1] = 64 / 255.0;
			color[2] = 192 / 255.0;
			break;
			//  Select orange color
		case 9:
			color[0] = 255 / 255.0;
			color[1] = 192 / 255.0;
			color[2] = 64 / 255.0;
			break;
			//  Select pink color
		case 10:
			color[0] = 255 / 255.0;
			color[1] = 0 / 255.0;
			color[2] = 255 / 255.0;
			break;
			//  Select red color
		case 11:
			color[0] = 255 / 255.0;
			color[1] = 0 / 255.0;
			color[2] = 0 / 255.0;
			break;
			//  Select white color
		case 12:
			color[0] = 255 / 255.0;
			color[1] = 255 / 255.0;
			color[2] = 255 / 255.0;
			break;
			//  Select yellow color
		case 13:
			color[0] = 255 / 255.0;
			color[1] = 255 / 255.0;
			color[2] = 0 / 255.0;
			break;
		}
		*/

		printf("Item %d selected.\n", listbox_item_id);

		break;

		//  Quit Button clicked
	case QUIT_BUTTON:

		printf("Quit Button clicked... Exit!\n");

		exit(1);

		break;
	
	default:
		printf("defaulted on input\n");
		break;
	}
}

//-------------------------------------------------------------------------
//  Idle Callback function.
//
//  Set the main_window as the current window to avoid sending the
//  redisplay to the GLUI window rather than the GLUT window. 
//  Call the Sleep function to stop the GLUI program from causing
//  starvation.
//-------------------------------------------------------------------------
void idle()
{
	glutSetWindow(main_window);
	glutPostRedisplay();
	Sleep(50);
}


//*************************************************************************
//  Program Main method.
//*************************************************************************
void main(int argc, char **argv)
{

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
	main_window = glutCreateWindow(window_title);

	//  View in full screen if the full_screen flag is on
	if(full_screen)
		glutFullScreen();

	//  Set OpenGL context initial state.
	init();

	// Set the GLUT callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	//  Setup all GLUI stuff
	setupGLUI();

	//  Start GLUT event processing loop
	glutMainLoop();
}

