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
	// XXX
	renderWindow._test_run();
	
	return 0;
}

} // end namespace bdEngine
