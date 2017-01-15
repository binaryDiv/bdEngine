#include <iostream>

#include "Engine.h"

int main(int argc, char* argv[]) {
	int exitCode = 0;
	
	try {
		// Create and initialize engine
		bdEngine::Engine engine {argc, argv};
		
		// std::cout << "press q to quit" << std::endl;
		// std::cout << "press k to turn left" << std::endl;
		// std::cout << "press l to turn right" << std::endl;
		
		// Handle control to engine
		exitCode = engine.run();
	}
	catch (std::exception& e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
		exitCode = 1;
	}
	catch (...) {
		std::cerr << "Caught unknown exception\n";
		exitCode = 1;
	}
	
	return exitCode;
}
