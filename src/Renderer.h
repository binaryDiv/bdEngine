#ifndef _BDENGINE_RENDERER_H
#define _BDENGINE_RENDERER_H

// GLEW has to be included *before* GLFW or any other OpenGL header.
#include <GL/glew.h>
#include "GLFWpp.h"

#include "GLShaderProgram.h"
#include "Image.h"
#include "Texture2D.h"

namespace bdEngine {

class Renderer {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	Renderer();
	~Renderer();
	
	// --- Forbid copy and move operations
	Renderer(const Renderer& other)            = delete;  // copy constructor
	Renderer& operator=(const Renderer& other) = delete;  // copy assignment
	Renderer(Renderer&& other)                 = delete;  // move constructor
	Renderer& operator=(Renderer&& other)      = delete;  // move assignment
	
	
	/*******************************************************************
	 * Drawing / Rendering
	 *******************************************************************/
	
	// Set the size of the window
	void setWindowSize(const int width, const int height);
	
	// Draw one frame
	void drawFrame();
	
	// Switch between wireframe and filling mode
	bool toggleWireframeMode();
	
private:
	// Shader program object
	GLShaderProgram shaderProgram;
	
	// XXX Example objects
	GLuint exVAO;  // Vertex Array Object
	GLuint exVBO;  // Vertex Buffer Object
	GLuint exEBO;  // Element Buffer Object
	
	// Example textures
	Texture2D exTexture1;
	Texture2D exTexture2;
	
	// Settings
	bool wireframeMode = false;
};

} // end namespace bdEngine

#endif /* end of include guard: _BDENGINE_RENDERER_H */
