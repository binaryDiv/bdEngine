#include "GLShaderProgram.h"

// TODO implement own logging class
#include <iostream>

namespace bdEngine {

/*******************************************************************
 * Construction and destruction
 *******************************************************************/

// Constructor
GLShaderProgram::GLShaderProgram() {
	// Create shader program object
	programID = glCreateProgram();
}

// Destructor
GLShaderProgram::~GLShaderProgram() {
	// Free all shader objects
	for (auto &i : vecShaderIDs) {
		glDeleteShader(i);
	}
	
	// Free program object
	if (programID) {
		glDeleteProgram(programID);
	}
}


/*******************************************************************
 * Compiling and linking
 *******************************************************************/

bool GLShaderProgram::addShader(const GLchar * const * ppcSrc, GLenum shaderType) {
	// Create shader object
	GLuint shaderID = glCreateShader(shaderType);
	
	if (shaderID == 0) {
		// XXX throw exception?
		return false;
	}
	
	// Add shader ID to vector
	vecShaderIDs.push_back(shaderID);
	
	// Compile shader
	glShaderSource(shaderID, 1, ppcSrc, nullptr);
	glCompileShader(shaderID);
	
	// Check for compile errors
	GLint compileStatus = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
	
	if (!compileStatus) {
		// TODO better error handling, exceptions maybe?
		GLint errorLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &errorLength);
		
		GLchar* errorMessage = new GLchar[errorLength];
		if (errorMessage == nullptr) {
			// TODO throw exception?
			return false;
		}
		
		glGetShaderInfoLog(shaderID, errorLength, &errorLength, errorMessage);
		std::cerr << "Compile error for shader " << shaderType << ": " << errorMessage << std::endl;
		delete[] errorMessage;
		return false;
	}
	
	// Attach shader to program
	glAttachShader(programID, shaderID);
	
	return true;
}

bool GLShaderProgram::linkShaders() {
	// Link shaders to program
	glLinkProgram(programID);
	
	// Check for linking errors
	GLint linkingStatus = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkingStatus);
	
	if (!linkingStatus) {
		// TODO better error handling, exceptions maybe?
		GLint errorLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &errorLength);
		
		GLchar* errorMessage = new GLchar[errorLength];
		if (errorMessage == nullptr) {
			// TODO throw exception?
			return false;
		}
		
		glGetProgramInfoLog(programID, errorLength, &errorLength, errorMessage);
		std::cerr << "Linker error: " << errorMessage << std::endl;
		delete[] errorMessage;
		return false;
	}
	
	return true;
}

void GLShaderProgram::useProgram() {
	// Make shader program current
	glUseProgram(programID);
}


/*******************************************************************
 * Properties and information
 *******************************************************************/

GLint GLShaderProgram::getAttribLocation(const GLchar* name) {
	return glGetAttribLocation(programID, name);
}

GLint GLShaderProgram::getUniformLocation(const GLchar* name) {
	return glGetUniformLocation(programID, name);
}


} // end namespace bdEngine
