#include "Renderer.h"

namespace bdEngine {

/*******************************************************************
 * Construction and destruction
 *******************************************************************/

// Default constructor
Renderer::Renderer()
{
	// Initialize OpenGL
	
	// Set background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	// TODO This is just a placeholder class.
}

Renderer::~Renderer() {
}


/*******************************************************************
 * Drawing / Rendering
 *******************************************************************/

void Renderer::setWindowSize(const int width, const int height) {
	// Set viewport
	glViewport(0, 0, width, height);
}

void Renderer::drawFrame() {
	// Clear frame and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// TODO This is just a placeholder class.
}

} // end namespace bdEngine
