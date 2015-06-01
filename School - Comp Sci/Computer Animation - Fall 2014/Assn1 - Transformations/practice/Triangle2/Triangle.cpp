

#include <stdio.h>
#include <stdlib.h>

//use glew.h instead of gl.h to get of the GL prototypes declared
#include <GL/glew.h>

//using the glut library for the base windowing set up
#include <GL/glut.h>

//program handle
GLuint program;

//going to use this to pass each triangle vertex to the vertex shader
GLint attribute_coord2d;

int init_resources(void);
void onDisplay();
void free_resources(void);

int main(int argc, char* argv[]){

	//glut related initializing functions
	glutInit(&argc, argv);
	//glutInitContextVersion(2, 0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("My First Triangle");

	//Extension wrangler initializing
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK){
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}

	//when all init functions run without errors the program can initialize the resources
	if (1 == init_resources()){
		//we can display it if everything goes okay
		glutDisplayFunc(onDisplay);
		glutMainLoop();
	}

	//if the program exits in the usual way, free resources and exit with a success
	free_resources();
	return EXIT_SUCCESS;
}

/** Function: init_resources
* Receives: void
* Returns: int
* This function creates all GLSL related stuff
* returns 1 when all is ok, 0 with a displayed error
*/
int init_resources(void){
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

	//this code initializes the vertex shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char* vs_source =

#ifdef GL_ES_VERSION_2_0
		"#version 100\n"  // OpenGL ES 2.0
#else
		"#version 120\n"  // OpenGL 2.1
#endif
		"attribute vec2 coord2d;                  "
		"void main(void) {                        "
		"  gl_Position = vec4(coord2d, 0.0, 1.0); "
		"}";
	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == 0){
		fprintf(stderr, "Error in vertex shader\n");
		return 0;
	}

	//this code initializes the fragment shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fs_source =
		"version 120		    \n"
		"void main(void){	      "
		"  gl_FragColor[0] = 0.0; "
		"  gl_FragColor[1] = 0.0; "
		"  gl_FragColor[2] = 1.0; "
		"}";
	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
	if (!compile_ok){
		fprintf(stderr, "Error in fragment shader\n");
		return 0;
	}

	//this code is going to link the vertex and fragment shaders
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok){
		fprintf(stderr, "glLinkProgram:");
		return 0;
	}

	//here we bind the attribute to the program
	const char* attribute_name = "coord2d";
	attribute_coord2d = glGetAttribLocation(program, attribute_name);
	if (attribute_coord2d == -1){
		fprintf(stderr, "Could not bing attribute %s\n", attribute_name);
		return 0;
	}

	return 1;
}

void onDisplay(){
	//clear the background as white
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glEnableVertexAttribArray(attribute_coord2d);
	GLfloat triangle_vertices[] = {
		0.0f, 0.8f,
		-0.8f, -0.8f,
		0.8f, -0.8f
	};

	//push each element to the vertex shader
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(attribute_coord2d);

	//Display the result
	glutSwapBuffers();

	//Describe our vertices array to OpenGL (it can't guess its format automatically)
	glVertexAttribPointer(
		attribute_coord2d,  //attribute
		2,					//number of elements per vertex, here (x,y)
		GL_FLOAT,			//the type of each element
		GL_FALSE,			//take our values as-is
		0,					//no extra data between each position
		triangle_vertices   //pointer to the c array
		);
}

void free_resources(void){
	glDeleteProgram(program);
}
