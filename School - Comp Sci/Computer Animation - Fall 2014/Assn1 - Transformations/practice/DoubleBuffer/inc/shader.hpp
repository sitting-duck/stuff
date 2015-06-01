#ifndef SHADER_H
#define SHADER_H 1

#include <GL/glew.h>
#include <GL/glut.h>

class Shader {
	public:
						Shader					();
						Shader					(const char * shaderSource, GLenum shaderType);
						~Shader					();
		
		GLuint			load					(const char * shaderSource, GLenum shaderType);
		void			unload					();
		GLuint			getHandle				();
		static void		logErrs					(GLuint shadObj);
		static void		logErrs					(const Shader & other);

	private:
		// no copying
						Shader					(const Shader & other);
		Shader &		copy					(const Shader & other);
		Shader &		operator =				(const Shader & other);

	protected:
						GLuint					shadHandle;		// handle to the compiled shader
};

inline GLuint Shader::getHandle () {
	return shadHandle;
}

inline void Shader::logErrs (const Shader & other) {
	logErrs (other.shadHandle);
}

#endif