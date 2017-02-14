#include "Engine.h"

#include <exception>

namespace bdEngine {

/*******************************************************************
 * Construction and destruction
 *******************************************************************/

// Default constructor
Engine::Engine() {
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

// Initialization
void Engine::init() {
	if (initialized_) {
		// Engine already is initialized!
		throw std::logic_error("Engine already initialized.");
	}
	
	// Create and initialize RenderWindow
	renderWindow_ = std::make_unique<RenderWindow>();
	
	// Initialized!
	initialized_ = true;
}

// Main loop (returns exit code)
int Engine::run() {
	// Ensure the engine is initialized.
	if (!initialized_) {
		throw std::logic_error("Engine not initialized.");
	}
	
	// Main loop: exit when window is closed
	while (renderWindow_->keepRunning()) {
		// Render the current frame
		renderWindow_->drawFrame();
		
		// Poll and handle events, call event handlers, etc.
		renderWindow_->handleEvents();
	}
	
	return 0;
}

} // end namespace bdEngine
