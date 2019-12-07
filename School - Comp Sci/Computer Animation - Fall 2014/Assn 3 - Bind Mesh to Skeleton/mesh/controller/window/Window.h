#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glui.h>
#include "Scene.h"

class Window{
public:
	Scene* scene;

	int main_window;
	GLUI* glui_window;
	GLUI_Panel* op_panel;

	int whichJointSelected;
	GLUI_Listbox* joint_listbox;
	//for identifying which item was picked from the joint listbox
	int listbox_item_id = 0;

	typedef void(*UpdateFunc) (int);

	//define the window position on screen
	int window_x;
	int window_y;

	//window size
	int window_width = 600;
	int window_height = 800;

	//controls are things like dropdown menus, list boxes etc.
	enum controls { JOINT_LISTBOX = 0 };

public:
	Window();
	Window(unsigned int height, unsigned int width, Scene& sceneRef);
	~Window();

	void init();

	void centerOnScreen();

	void onKeyBoardInput(unsigned char _key);

	void createOptionsWindow(UpdateFunc updateFunc);

	void createControls(UpdateFunc updateFunc);
	void onUpdateControl(int controlId);


};

#endif