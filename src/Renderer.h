#ifndef _BDENGINE_RENDERER_H
#define _BDENGINE_RENDERER_H

// GLEW has to be included *before* GLFW or any other OpenGL header.
#include <GL/glew.h>
#include "GLFWpp.h"

namespace bdEngine {

class Renderer {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	Renderer();
	~Renderer();
	
	
	/*******************************************************************
	 * Drawing / Rendering
	 *******************************************************************/
	
	// Set the size of the window
	void setWindowSize(const int width, const int height);
	
	// Draw one frame
	void drawFrame();
};

} // end namespace bdEngine

#endif /* end of include guard: _BDENGINE_RENDERER_H */
