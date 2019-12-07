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

//-------------------------------------------------------------------------
//  This function sets the window x and y coordinates
//  such that the window becomes centered
//-------------------------------------------------------------------------
void Window::centerOnScreen()
{
	window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
	window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
}

void Window::onKeyBoardInput(unsigned char _key)
{
	enum TransformMode{ CAMERA_MODE, JOINT_MODE };

	enum CameraTransforms{ CAMERA_ROTATE, CAMERA_TRANSLATE };

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
			currentCameraTransformsMode = CAMERA_TRANSLATE;
			std::cout << "camera translate mode" << std::endl;
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
		if(currentTransformMode == CAMERA_MODE  && currentCameraTransformsMode == CAMERA_ROTATE && currentAxis == AXIS_X){
			scene->camera.IncPitch();
			//std::cout << "inc pitch" << std::endl;

		}
		else if(currentTransformMode == CAMERA_MODE && currentCameraTransformsMode == CAMERA_ROTATE && currentAxis == AXIS_Y){
			scene->camera.IncYaw();
			//std::cout << "inc yaw" << std::endl;
		}
		else if(currentTransformMode == CAMERA_MODE && currentCameraTransformsMode == CAMERA_ROTATE && currentAxis == AXIS_Z){
			scene->camera.IncRoll();
			//std::cout << "inc roll" << std::endl;
		}
		else if(currentTransformMode == CAMERA_MODE && currentCameraTransformsMode == CAMERA_TRANSLATE && currentAxis == AXIS_X){
			
		}
		else if(currentTransformMode == CAMERA_MODE && currentCameraTransformsMode == CAMERA_TRANSLATE && currentAxis == AXIS_Y){

		}
		else if(currentTransformMode == CAMERA_MODE && currentCameraTransformsMode == CAMERA_TRANSLATE && currentAxis == AXIS_Z){
			scene->camera.decDistance();
		}
		else if(currentTransformMode == JOINT_MODE){
			scene->increaseRotateOfCurrentJoint(currentAxis);
			
			//update model
			scene->updateModel();

			//redraw model
			scene->drawModel();
		}
		break;
	case '-':
		if(currentTransformMode == CAMERA_MODE && currentCameraTransformsMode == CAMERA_ROTATE && currentAxis == AXIS_X){
			scene->camera.DecPitch();
			//std::cout << "dec pitch" << std::endl;

		}
		else if(currentTransformMode == CAMERA_MODE && currentCameraTransformsMode == CAMERA_ROTATE && currentAxis == AXIS_Y){
			scene->camera.DecYaw();
			//std::cout << "dec yaw" << std::endl;
		}
		else if(currentTransformMode == CAMERA_MODE && currentCameraTransformsMode == CAMERA_ROTATE && currentAxis == AXIS_Z){
			scene->camera.DecRoll();
			//std::cout << "dec roll" << std::endl;
		}
		else if(currentTransformMode == CAMERA_MODE && currentCameraTransformsMode == CAMERA_TRANSLATE && currentAxis == AXIS_X){

		}
		else if(currentTransformMode == CAMERA_MODE && currentCameraTransformsMode == CAMERA_TRANSLATE && currentAxis == AXIS_Y){

		}
		else if(currentTransformMode == CAMERA_MODE && currentCameraTransformsMode == CAMERA_TRANSLATE && currentAxis == AXIS_Z){
			scene->camera.incDistance();
		}
		else if(currentTransformMode == JOINT_MODE){
			scene->decreaseRotateOfCurrentJoint(currentAxis);
			
			//update model
			scene->updateModel();

			//redraw model
			scene->drawModel();
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

	scene->camera.Draw();
	glutPostRedisplay();
}

void Window::createOptionsWindow(UpdateFunc updateFunc){
	//  Create GLUI window
	glui_window = GLUI_Master.create_glui("Options", 0, window_x - 235, window_y);

	//add a panel to the glui window
	op_panel = glui_window->add_panel(" Options ");;

	//GLUI* glui = GLUI_Master.create_glui(" ", 0, 670, 50);
	joint_listbox = glui_window->add_listbox_to_panel(op_panel, "  Select Joint  ", &listbox_item_id, JOINT_LISTBOX, updateFunc);

	//add all the joints to joint list box
	for(int i = 0; i < scene->model->getSkelNumJoints(); i++){
		joint_listbox->add_item(i, scene->model->getSkeleton()->operator[](i).getName().c_str());
	}

	//select the root by default
	joint_listbox->set_int_val(0);

	//empty space
	for(int i = 0; i < 40; i++){
		//glui_window->add_separator();
		glui_window->add_statictext("");
	}
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