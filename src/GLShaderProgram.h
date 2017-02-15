#ifndef _BDENGINE_GLSHADERPROGRAM_H
#define _BDENGINE_GLSHADERPROGRAM_H

#include <GL/glew.h>

#include <vector>

namespace bdEngine {

class GLShaderProgram {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	GLShaderProgram();
	~GLShaderProgram();
	
	// --- Forbid copy and move operations
	GLShaderProgram(const GLShaderProgram& other)            = delete;  // copy constructor
	GLShaderProgram& operator=(const GLShaderProgram& other) = delete;  // copy assignment
	GLShaderProgram(GLShaderProgram&& other)                 = delete;  // move constructor
	GLShaderProgram& operator=(GLShaderProgram&& other)      = delete;  // move assignment
	
	
	/*******************************************************************
	 * Compiling and linking
	 *******************************************************************/
	
	/*!
	 * Returns the internal ID of the shader program object.
	 */
	GLuint getProgramID() const {
		return programID;
	}
	
	/*!
	 * Adds a shader of a certain type and compiles it.
	 * Prints error message and returns false if compilation fails.
	 */
	bool addShader(const GLchar * const * ppcSrc, GLenum shaderType);
	
	/*!
	 * Links all shaders to the program.
	 * Prints error message and returns false if linking fails.
	 */
	bool linkShaders();
	
	/*!
	 * Makes this program current.
	 */
	void useProgram();
	
	
	/*******************************************************************
	 * Properties and information
	 *******************************************************************/
	
	/*!
	 * Returns the location of a named attribute.
	 */
	GLint getAttribLocation(const GLchar* name);
	
	/*!
	 * Returns the location of a named uniform.
	 */
	GLint getUniformLocation(const GLchar* name);
	
protected:
	// Internal program ID
	GLuint programID = 0;
	
	// Shader IDs that belong to this program
	std::vector<GLuint> vecShaderIDs;
};

} // end namespace bdEngine

#endif /* end of include guard: _BDENGINE_RENDERWINDOW_H */
