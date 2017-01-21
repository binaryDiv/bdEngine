#include "Engine.h"

namespace bdEngine {


/*******************************************************************
 * Construction and destruction
 *******************************************************************/

// Default constructor
Engine::Engine() {
	// TODO Template stub
}

// Constructor with application argument parsing
Engine::Engine(int& argc, char**& argv)
	: Engine()
{
	// TODO Parse application arguments
}


/*******************************************************************
 * Engine lifecycle
 *******************************************************************/

// Main loop (returns exit code)
int Engine::run() {
	// Make window context current
	renderWindow.activateContext();
	
	// Main loop: exit when window is closed
	while (renderWindow.keepRunning()) {
		// Prepare render window to begin rendering one frame.
		renderWindow.beginFrame();
		
		
		// TODO DO THE RENDERY THING
		
		// XXX -> move to Renderer
		glViewport(0, 0, renderWindow.getFramebufferWidth(),
			renderWindow.getFramebufferHeight());
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		// End rendering of this frame, swap buffers, etc.
		renderWindow.endFrame();
		
		// Poll and handle events, call event handlers, etc.
		renderWindow.handleEvents();
	}
	
	return 0;
}

} // end namespace bdEngine
