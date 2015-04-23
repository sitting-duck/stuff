#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glui.h>
#include "Scene.h"

class Window{
public:
	Scene* scene;

	int main_window;
	GLUI* glui_window;
	GLUI_Panel* leftPanel;

	int whichJointSelected;

	GLUI_Listbox* joint_listbox;


	typedef void(*UpdateFunc) (int);

public:
	Window();
	Window(unsigned int height, unsigned int width, Scene& sceneRef);
	~Window();

	void init();
	void createControls(UpdateFunc updateFunc);
	void onUpdateControl(int controlId);


};

#endif