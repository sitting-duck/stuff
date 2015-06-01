#include "Window.h"
#include <GL/glui.h>

Window::Window(){}

Window::Window(unsigned int height, unsigned int width, Scene& sceneRef){
	
	scene = &sceneRef;

	

	

	glui_window = GLUI_Master.create_glui("  Assn3  ");

	//leftPanel = glui_window->add_panel("  Stuuuuuuff  ");

}

Window::~Window(){

}

void Window::init(){

	
}

void Window::createControls(UpdateFunc updateFunc){
	
	//joint_listbox = glui_window->add_listbox("  Select Joint  ", &scene->currJoint, JOINT_LISTBOX, updateFunc);
	//
	////add all the joints to joint list box
	//for(int i = 0; i < scene->model->getSkelNumJoints(); i++){
	//	joint_listbox->add_item(i, scene->model->getSkeleton()->operator[](i).getName().c_str());
	//}
}

void Window::onUpdateControl(int controlId){
	std::cout << "A CONTROL WAS UPDATED OMG!!!" << std::endl;

	switch(controlId){
	case 0:
		//the item selected from the box will become the currJoint
		std::cout << "selected: " << whichJointSelected << std::endl;
		break;
	}

	glutPostRedisplay();
}